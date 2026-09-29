//go:build goexperiment.simd && (amd64 || arm64)

package main

import (
	"strings"
	"testing"
)

// Oracle scalaire de référence sur []byte pour comparaison bit-exacte.
func scalarLexStringOracle(input []byte) int {
	if len(input) == 0 || input[0] != '"' {
		return -1
	}
	cursor := 1
	start := 1
	n := len(input)

	for cursor < n {
		b := input[cursor]
		if b == '"' {
			return cursor - start
		}
		if b == '\\' {
			cursor++
			if cursor < n {
				esc := input[cursor]
				if esc == '\\' || esc == '"' || esc == '/' || esc == 'b' || esc == 'f' || esc == 'n' || esc == 'r' || esc == 't' {
					cursor++
					continue
				}
			}
			return -1
		}
		if b == 0 || b == '\n' || b == '\r' {
			return -1
		}
		cursor++
	}
	return -1
}

func TestSIMDLexer_ParityVsOracle(t *testing.T) {
	testCases := []struct {
		name  string
		input string
	}{
		{"Chaîne vide", "\"\""},
		{"Chaîne courte", "\"court\""},
		{"Chaîne exacte 31 octets", "\"" + strings.Repeat("A", 31) + "\""},
		{"Chaîne exacte 32 octets", "\"" + strings.Repeat("B", 32) + "\""},
		{"Chaîne longue 256 octets", "\"" + strings.Repeat("C", 256) + "\""},
		{"Chaîne avec échappements simples", "\"texte avec \\n et \\\"guillemets\\\" et \\t fin\""},
		{"Échappement en limite de bloc 32", "\"" + strings.Repeat("X", 31) + "\\\"" + strings.Repeat("Y", 31) + "\""},
		{"Erreur caractère interdit LF", "\"texte avant \n suite\""},
		{"Erreur séquence non fermée avec sentinelle", "\"texte sans fermeture\x00"},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			inputBytes := []byte(tc.input)
			expected := scalarLexStringOracle(inputBytes)
			actual := LexString(inputBytes)
			if actual != expected {
				t.Fatalf("Divergence sur %q : attendu %d, obtenu %d", tc.input, expected, actual)
			}
		})
	}
}

func TestSIMDLexer_ZeroAllocation(t *testing.T) {
	payload := []byte("\"" + strings.Repeat("Moteur_Vectoriel_Souverain_", 100) + "\"")
	allocs := testing.AllocsPerRun(1000, func() {
		res := LexString(payload)
		if res <= 0 {
			t.Fatalf("Échec inattendu : %d", res)
		}
	})

	if allocs != 0 {
		t.Fatalf("Violation Règle Zéro Allocation : %f allocs/op (attendu 0.0)", allocs)
	}
}

func BenchmarkSIMDLexer_Throughput(b *testing.B) {
	rawChunk := strings.Repeat("Champ_Donnees_Pour_Benchmark_SIMD_1234567890_", 20)
	payload := []byte("\"" + strings.Repeat(rawChunk, 1000) + "\"")
	b.SetBytes(int64(len(payload)))
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		res := LexString(payload)
		if res <= 0 {
			b.Fatalf("Erreur de tokenisation")
		}
	}
}

func BenchmarkScalarLexer_Throughput(b *testing.B) {
	rawChunk := strings.Repeat("Champ_Donnees_Pour_Benchmark_SIMD_1234567890_", 20)
	payload := []byte("\"" + strings.Repeat(rawChunk, 1000) + "\"")
	b.SetBytes(int64(len(payload)))
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		res := LexStringScalar(payload)
		if res <= 0 {
			b.Fatalf("Erreur de tokenisation")
		}
	}
}

