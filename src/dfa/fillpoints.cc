#include <stddef.h>
#include <limits>
#include <stack>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/util/check.h"

// note [finding strongly connected components of DFA]
//
// A slight modification of Tarjan's algorithm.
//
// The algorithm traverses the TDFA in depth-first order. It maintains a stack of states that have
// already been visited but haven't been assigned to an SCC yet. For each state the algorithm
// calculates 'lowlink': index of the highest ancestor state reachable in one step from a descendant
// of this state. Lowlink is used to determine when a set of states should be popped off stack into
// a new SCC.
//
// We use lowlink to hold different kinds of information:
//   - values in range [0 .. stack size] mean that the state is on stack (a link to a state with the
//     smallest index reachable from this one)
//   - SCC_UND means that this state has not been visited yet
//   - SCC_INF means that this state has already been popped off stack
//
// We use stack size (rather than topological sort index) as a unique index of the state on stack.
// This is safe because the indices of states on stack are unique and less than the indices of
// states that have been popped off stack (SCC_INF).

namespace re2c {
namespace {

static constexpr size_t SCC_INF = std::numeric_limits<size_t>::max();
static constexpr size_t SCC_UND = SCC_INF - 1;

static bool loopback(size_t state, size_t narcs, const size_t* arcs) {
    for (size_t i = 0; i < narcs; ++i) {
        if (arcs[i] == state) return true;
    }
    return false;
}

struct StackItem {
    size_t state;  // current state
    size_t symbol; // next arc to be visited in this state
    size_t link;   // Tarjan's "lowlink"
};

// Tarjan's algorithm
static void scc(const Tdfa& dfa, std::vector<bool>& trivial, std::vector<StackItem>& stack_dfs) {
    std::vector<size_t> lowlink(dfa.states.size(), SCC_UND);
    std::stack<size_t> stack;

    stack_dfs.push_back({0, 0, 0});

    while (!stack_dfs.empty()) {
        const size_t i = stack_dfs.back().state;
        size_t c = stack_dfs.back().symbol;
        size_t link = stack_dfs.back().link;
        stack_dfs.pop_back();

        const size_t* arcs = dfa.states[i]->arcs;

        if (c == 0) {
            // DFS recursive enter
            DCHECK(lowlink[i] == SCC_UND);
            link = lowlink[i] = stack.size();
            stack.push(i);
        } else {
            // DFS recursive return (from one of successor states)
            const size_t j = arcs[c - 1];
            DCHECK(lowlink[j] != SCC_UND);
            lowlink[i] = std::min(lowlink[i], lowlink[j]);
        }

        // find the next successor state that hasn't been visited yet
        for (; c < dfa.nchars; ++c) {
            const size_t j = arcs[c];
            if (j != Tdfa::NIL) {
                if (lowlink[j] == SCC_UND) {
                    break;
                }
                lowlink[i] = std::min(lowlink[i], lowlink[j]);
            }
        }

        if (c < dfa.nchars) {
            // recurse into the next successor state
            stack_dfs.push_back({i, c + 1, link});
            stack_dfs.push_back({arcs[c], 0, SCC_UND});
        } else if (lowlink[i] == link) {
            // All successors have been visited. An SCC is non-trivial (it has loops) if either:
            //   - it contains multiple interconnected states, or
            //   - it contains a single self-looping state
            trivial[i] = i == stack.top() && !loopback(i, dfa.nchars, arcs);

            for (;;) {
                const size_t j = stack.top();
                stack.pop();
                lowlink[j] = SCC_INF;
                if (i == j) break;
            }
        }
    }
}

static void calc_fill(const Tdfa& dfa,
                      const std::vector<bool>& trivial,
                      std::vector<StackItem>& stack_dfs,
                      std::vector<size_t>& fill) {
    const size_t nstates = dfa.states.size();
    fill.resize(nstates, SCC_UND);

    stack_dfs.push_back({0, 0, SCC_INF});

    while (!stack_dfs.empty()) {
        const size_t i = stack_dfs.back().state;
        size_t c = stack_dfs.back().symbol;
        stack_dfs.pop_back();

        const size_t* arcs = dfa.states[i]->arcs;

        if (c == 0) {
            // DFS recursive enter
            if (fill[i] != SCC_UND) continue;
            fill[i] = 0;
        } else {
            // DFS recursive return (from one of successor states)
            const size_t j = arcs[c - 1];
            DCHECK(fill[i] != SCC_UND && fill[j] != SCC_UND);
            fill[i] = std::max(fill[i], 1 + (trivial[j] ? fill[j] : 0));
        }

        // find the next successor state that hasn't been visited yet
        for (; c < dfa.nchars; ++c) {
            const size_t j = arcs[c];
            if (j != Tdfa::NIL) break;
        }

        if (c < dfa.nchars) {
            // recurse into the next successor state
            stack_dfs.push_back({i, c + 1, SCC_INF});
            stack_dfs.push_back({arcs[c], 0, SCC_INF});
        }
    }

    // The following states must trigger YYFILL:
    //   - inital state
    //   - all states in non-trivial SCCs
    // for other states, reset YYFILL argument to zero
    for (size_t i = 1; i < nstates; ++i) {
        if (trivial[i]) {
            fill[i] = 0;
        }
    }
}

} // anonymous namespace

void fillpoints(const Tdfa& dfa, std::vector<size_t>& fill) {
    const size_t nstates = dfa.states.size();
    std::vector<bool> trivial(nstates, false);
    std::vector<StackItem> stack_dfs;
    stack_dfs.reserve(nstates);

    // Find TDFA states that belong to non-trivial SCCs.
    scc(dfa, trivial, stack_dfs);

    // For each state, calculate YYFILL argument (the maximum path length to the next YYFILL state).
    calc_fill(dfa, trivial, stack_dfs, fill);
}

} // namespace re2c
