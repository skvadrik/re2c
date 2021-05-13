/*
 * @(#)ReTdfa.jpp       1.0 2017/10/05
 *
 * Copyright (c) 2016 Angelo Borsotti. All Rights Reserved.
 * This computer program is protected under Copyright.
 */

import java.lang.reflect.*;
import java.io.*;
import java.util.*;
import re2c.RE2C;

/**
 * The <code>ReTdfa</code> class provides regular expression parsing with the TDFA
 * Ulya Trofimovich's algorithm and its evolutions.
 *
 * @author  Angelo Borsotti
 * @version 1.0   5 October 2017
 */

public class ReTdfa {

    /** Whether circular bijections are allowed. */
    private boolean bijCyclic = false;

    /** Whether dfs closure is used. */
    private boolean dfsClosure = false;

    /** Whether the TNFA is used to match or the TDFA. */
    private boolean useTnfa = false;

    /** Whether the compressed transition table is used. */
    private boolean transtable = true;

    /** Whether register tries are used. */
    private boolean regTrie = false;

    /** Whether fixed tags are detected and optimized. */
    private boolean fixedTags = true;

    /** Whether TNFA uses incremental disambiguation. */
    private boolean incremental = false;

    /** Whether matching is done without tags. */
    private boolean tagless = false;

    /** Whether tagless matching delivers final registers. */
    private boolean finreg = false;

    /** Whether tagless matching delivers final registers with subhistories separators. */
    private boolean subhist = false;

    /** Whether the .x component is used to build the final tstring, or the path component. */
    private boolean xcomp = false;

    /** Whether matching delivers offsets. */
    private boolean offsets = false;

    /** Whether matching delivers only the last values of registers. */
    private boolean lastval = false;

    /** Whether tagless matching is done in 1 pass. */
    private boolean onepass = false;

    /** Whether tagless matching produces a parse tree. */
    private boolean parsetree = false;

    /** Whether Okui's disambiguation is used. */
    private boolean okui = false;

    /** Whether the new (newpaper) shape of the TNFA is used. */
    private boolean newTNFA = false;

    //---------------- libre2c ---------------------

    /** use libre2c */
    private boolean re2c = false;

    /** libre2c: use TNFA-based algorithms */
    private boolean re2c_nfa = false;

    /** libre2c: use JIT-determinization */
    private boolean re2c_jit = false;

    /** libre2c: use registerless-TDFA */
    private boolean re2c_regless = false;

    /** libre2c: extract tag subhistory on all repetitions */
    private boolean re2c_subhist = false;

    /** libre2c: return result as a t-string */
    private boolean re2c_tstring = false;

    /** libre2c: automatically add tags to all subexpressions */
    private boolean re2c_autotags = false;

    /** libre2c: foreign pointer to a C++ regex_t structure */
    private long re2c_reg = 0;

    /** libre2c: the original regular expression */
    private String re2c_re;

    //---------------- Tracing ---------------------

    /** The compile time. */
    private long compileTime;

    /** The parse time. */
    private long parseTime;

    //---------------- Tracing ---------------------

    /** The trace stream. */

    private static class Trc {
        public static PrintStream out = System.err;
    }

    //---------------- Memory ---------------------

    /** The name of this variant of algorithm. */
    private String name;

    /**
     * Construct a new <code>ReTdfa</code>.
     */

    ReTdfa(){
    } 

    /**
     * Construct a new <code>ReTdfa</code> with the specified options.
     *
     * @param      name name for the options
     * @param      s string of comma-separated options
     */

    ReTdfa(String name, String options){
        this();
        setOptions(name,options);
    }

    /**
     * Set in this object the specified name and options.
     *
     * @param      name name for the options
     * @param      s string of comma-separated options
     */

    void setOptions(String name, String options){
        this.name = name;
        if (options.indexOf("negtags=inherit") < 0) this.negtags = false;
        if (options.indexOf("altbin=inherit") < 0) this.altbin = false;
        if (options.indexOf("concbin=inherit") < 0) this.concbin = false;
        if (options.indexOf("noGRO=inherit") < 0) this.noGRO = false;
        if (options.indexOf("autotags=inherit") < 0) this.autotags = false;
        if (options.indexOf("posix=inherit") < 0) this.posix = false;
        if (options.indexOf("matchTstring=inherit") < 0) this.matchTstring = false;
        if (options.indexOf("lookahead=inherit") < 0) this.lookahead = false;
        if (options.indexOf("bijCyclic=inherit") < 0) this.bijCyclic = false;
        if (options.indexOf("transtable=inherit") < 0) this.transtable = false;
        if (options.indexOf("regTrie=inherit") < 0) this.regTrie = false;
        if (options.indexOf("fixedTags=inherit") < 0) this.fixedTags = false;
        if (options.indexOf("incremental=inherit") < 0) this.incremental = false;
        if (options.indexOf("useTnfa=inherit") < 0) this.useTnfa = false;
        if (options.indexOf("tagless=inherit") < 0) this.tagless = false;
        if (options.indexOf("finreg=inherit") < 0) this.finreg = false;
        if (options.indexOf("subhist=inherit") < 0) this.subhist = false;
        if (options.indexOf("xcomp=inherit") < 0) this.xcomp = false;
        if (options.indexOf("offsets=inherit") < 0) this.offsets = false;
        if (options.indexOf("lastval=inherit") < 0) this.lastval = false;
        if (options.indexOf("onepass=inherit") < 0) this.onepass = false;
        if (options.indexOf("parsetree=inherit") < 0) this.parsetree = false;
        if (options.indexOf("okui=inherit") < 0) this.okui = false;
        if (options.indexOf("dfsClosure=inherit") < 0) this.dfsClosure = false;
        if (options.indexOf("onetag=inherit") < 0) this.onetag = false;
        if (options.indexOf("re2c=inherit") < 0) this.re2c = false;
        if (options.indexOf("re2c_nfa=inherit") < 0) this.re2c_nfa = false;
        if (options.indexOf("re2c_jit=inherit") < 0) this.re2c_jit = false;
        if (options.indexOf("re2c_regless=inherit") < 0) this.re2c_regless = false;
        if (options.indexOf("re2c_subhist=inherit") < 0) this.re2c_subhist = false;
        if (options.indexOf("re2c_tstring=inherit") < 0) this.re2c_tstring = false;
        if (options.indexOf("re2c_autotags=inherit") < 0) this.re2c_autotags = false;
        if (options.length() == 0) return;
        String[] opt = options.split(",");
        for (int i = 0; i < opt.length; i++){
            switch(opt[i]){
            case "negtags": this.negtags = true; break;
            case "altbin": this.altbin = true; break;
            case "concbin": this.concbin = true; break;
            case "noGRO": this.noGRO = true; break;
            case "autotags": this.autotags = true; break;
            case "posix": this.posix = true; break;
            case "matchTstring": this.matchTstring = true; break;
            case "lookahead": this.lookahead = true; break;
            case "bijCyclic": this.bijCyclic = true; break;
            case "transtable": this.transtable = true; break;
            case "regTrie": this.regTrie = true; break;
            case "fixedTags": this.fixedTags = true; break;
            case "incremental": this.incremental = true; break;
            case "useTnfa": this.useTnfa = true; break;
            case "tagless": this.tagless = true; break;
            case "finreg": this.finreg = true; break;
            case "subhist": this.subhist = true; break;
            case "xcomp": this.xcomp = true; break;
            case "offsets": this.offsets = true; break;
            case "lastval": this.lastval = true; break;
            case "onepass": this.onepass = true; break;
            case "parsetree": this.parsetree = true; break;
            case "okui": this.okui = true; break;
            case "dfsClosure": this.dfsClosure = true; break;
            case "onetag": this.onetag = true; break;
            case "re2c": this.re2c = true; break;
            case "re2c_nfa": this.re2c_nfa = true; break;
            case "re2c_jit": this.re2c_jit = true; break;
            case "re2c_regless": this.re2c_regless = true; break;
            case "re2c_subhist": this.re2c_subhist = true; break;
            case "re2c_tstring": this.re2c_tstring = true; break;
            case "re2c_autotags": this.re2c_autotags = true; break;
            default:
                String option = opt[i];
                int idx = opt[i].indexOf("=inherit");
                if (idx < 0){
                    System.out.printf("illegal option: %s\n",option);
                    new Throwable().printStackTrace(System.out);
                    System.exit(1);
                } else {
                    option = option.substring(0,idx);
                    switch(option){
                    case "negtags":
                    case "altbin":
                    case "concbin":
                    case "noGRO":
                    case "autotags":
                    case "posix":
                    case "matchTstring":
                    case "lookahead":
                    case "bijCyclic":
                    case "transtable":
                    case "regTrie":
                    case "fixedTags":
                    case "incremental":
                    case "useTnfa":
                    case "tagless":
                    case "finreg":
                    case "subhist":
                    case "xcomp":
                    case "offsets":
                    case "lastval":
                    case "onepass":
                    case "parsetree":
                    case "okui":
                    case "dfsClosure":
                    case "onetag":
                    case "re2c":
                    case "re2c_nfa":
                    case "re2c_jit":
                    case "re2c_regless":
                    case "re2c_subhist":
                    case "re2c_tstring":
                    case "re2c_autotags":
                        break;
                    default:
                        System.out.printf("illegal inherit option: %s\n",option);
                        new Throwable().printStackTrace(System.out);
                        System.exit(1);
                    }
                }
            }
        }
        if (this.onetag){
            this.posix = false;
            this.negtags = true;
            this.okui = false;
            this.autotags = false;
        } else {
            if (!this.autotags){
                this.okui = true;
            }
            if (this.okui){
                this.posix = true;
                this.negtags = true;
            }
            if (this.tagless){
                this.posix = true;
                this.negtags = true;
                this.okui = true;
            }
        }
        if (this.offsets){
//            this.autotags = false;
            this.finreg = true;
        } else {
            if (this.finreg){
                this.subhist = true;
            }
            if (this.subhist){
                this.xcomp = true;
            }
        }
        if (!this.tagless){
            this.subhist = true;
            this.xcomp = true;
        }
if (this.offsets) this.subhist = false;
    }

    /**
     * Deliver a string representing the current options.
     *
     * @return     string
     */

    private String optionsToString(){
        return String.format(
            "negtags: %s, altbin: %s, concbin: %s, noGRO: %s, autotags: %s, " +
            "posix: %s, matchTstring: %s, lookahead: %s, bijCyclic: %s, " +
            "transtable: %s, regTrie: %s, fixedTags: %s, incremental: %s, useTnfa: %s, " +
            "tagless: %s, finreg: %s, subhist: %s, xcomp: %s, offsets: %s, lastval: %s, onepass %s, " +
            "parsetree %s, okui %s, dfsClosure %s, onetag %s" +
            "re2c: %s, re2c_nfa: %s, re2c_jit: %s, re2c_regless: %s, re2c_subhist: %s, re2c_tstring: %s, re2c_autotags: %s, ",
            this.negtags,this.altbin,this.concbin,this.noGRO,this.autotags,
            this.posix,this.matchTstring,this.lookahead,this.bijCyclic,
            this.transtable,this.regTrie,this.fixedTags,this.incremental,this.useTnfa,
            this.tagless,this.finreg,this.subhist,this.xcomp,this.offsets,this.lastval,this.onepass,
            this.parsetree,this.okui,this.dfsClosure,this.onetag,
            this.re2c,this.re2c_nfa,this.re2c_jit,this.re2c_regless,this.re2c_subhist,this.re2c_tstring,this.re2c_autotags);
    }

    private String optionsString(){
        StringBuilder sb = new StringBuilder();
        if (this.negtags) sb.append("negtags,");
        if (this.altbin) sb.append("altbin,");
        if (this.concbin) sb.append("concbin,");
        if (this.noGRO) sb.append("noGRO,");
        if (this.autotags) sb.append("autotags,");
        if (this.posix) sb.append("posix,");
        if (this.matchTstring) sb.append("matchTstring,");
        if (this.lookahead) sb.append("lookahead,");
        if (this.bijCyclic) sb.append("bijCyclic,");
        if (this.transtable) sb.append("transtable,");
        if (this.regTrie) sb.append("regTrie,");
        if (this.fixedTags) sb.append("fixedTags,");
        if (this.incremental) sb.append("incremental,");
        if (this.useTnfa) sb.append("useTnfa,");
        if (this.tagless) sb.append("tagless,");
        if (this.finreg) sb.append("finreg,");
        if (this.subhist) sb.append("subhist,");
        if (this.xcomp) sb.append("xcomp,");
        if (this.offsets) sb.append("offsets,");
        if (this.lastval) sb.append("lastval,");
        if (this.onepass) sb.append("onepass,");
        if (this.parsetree) sb.append("parsetree,");
        if (this.okui) sb.append("okui,");
        if (this.dfsClosure) sb.append("dfsClosure,");
        if (this.onetag) sb.append("onetag,");
        if (this.re2c) sb.append("re2c,");
        if (this.re2c_nfa) sb.append("re2c_nfa,");
        if (this.re2c_jit) sb.append("re2c_jit,");
        if (this.re2c_regless) sb.append("re2c_regless,");
        if (this.re2c_subhist) sb.append("re2c_subhist,");
        if (this.re2c_tstring) sb.append("re2c_tstring,");
        if (this.re2c_autotags) sb.append("re2c_autotags,");
        if (sb.length() > 0){
            return sb.toString().substring(0,sb.length()-1);  // remove last comma
        }
        return sb.toString();
    }

    /**
     * Deliver the size in bytes of the specified array.
     *
     * @param     arr array
     * @return    size
     */

    static int arraySize(int[] arr){
        if (arr == null) return 0;
        int res = arr.length * 4 + 4;
        return res;
    }

    /**
     * Deliver the size in bytes of the specified array.
     *
     * @param     arr array
     * @return    size
     */

    static int arraySize(int[][] arr){
        if (arr == null) return 0;
        int res = arr.length * 4;
        for (int i = 0; i < arr.length; i++){
            if (arr[i] != null) res += arr[i].length * 4;
        }
        return res;
    }

    /** A growable array of integers. */

    protected static class IntVector implements Comparable
    {

        /** The container. */
        int[] arr;

        /** The number of elements. */
        int length;

        /** The number of elements added when enlarging. */
        private static final int QUANTUM = 10;

        /**
         * Construct an empty array.
         */

        IntVector(){
            this.arr = new int[QUANTUM];
            this.length = 0;
        }

        /**
         * Remove all the elements contained in this array, if any.
         */

        void clear(){
            this.length = 0;
        }

        /**
         * Enlarge the container ensuring that there is at least the specified space.
         *
         * @param      len space
         */

        void enlarge(int len){
            int newlen = this.arr.length + QUANTUM;
            if (this.arr.length - this.length < len){   // still not enough
                newlen += len - (this.arr.length - this.length);
            }
            if (newlen >= 1000){
                newlen *= 1.5;
            }
            this.arr = Arrays.copyOf(this.arr,newlen);
        }

        /**
         * Add the specified value at the end of this array.
         *
         * @param      value value to be appended
         */

        void add(int value){
            if (this.arr.length - this.length < 1){
                enlarge(1);
            }
            this.arr[this.length++] = value;
        }

        /**
         * Add the specified value at the specified index of this array.
         *
         * @param      index insertion index
         * @param      value value to be appended
         */

        void add(int index, int value){
            if (this.arr.length - this.length < 1){
                enlarge(1);
            }
            if (index < this.length){       // add in the middle
                System.arraycopy(this.arr,index,this.arr,index+1,this.length-index);  // shift
            }
            this.arr[index] = value;
            this.length++;
        }

        /**
         * Add all the values of the specified array at the end of the current one.
         *
         * @param      v array
         */

        void add(IntVector v){
            if (v == null) return;
            if (this.arr.length - this.length < v.length){
                enlarge(v.length);
            }
            System.arraycopy(v.arr,0,this.arr,this.length,v.length);
            this.length += v.length;
        }

        /**
         * Deliver the number of the elements currently contained in this array.
         *
         * @return     number of elements
         */

        int size(){
            return this.length;
        }

        /**
         * Deliver the value contained in the specified element.
         *
         * @param      idx index of the element
         * @return     value
         */

        int get(int idx){
            return this.arr[idx];
        }

        /**
         * Deliver a string representing the values contained in this array.
         *
         * @return     string
         */

        public String toString(){
            StringBuffer sb = new StringBuffer();
            boolean first = true;
            sb.append("[");
            for (int i = 0; i < this.length; i++){
                if (!first) sb.append(",");
                first = false;
                sb.append(this.arr[i]);
            }
            sb.append("]");
            return sb.toString();
        }

        /**
         * Tell if this array contains the same elements and in the same order as the
         * specified array.
         *
         * @param      other other array
         * @return     <code>true</code> if they are equal, and <code>false</code> otherwise.
         */

        public boolean equals(IntVector other){
            if (this.length != other.length) return false;
            for (int i = 0; i < this.length; i++){
                if (this.arr[i] != other.arr[i]) return false;
            }
            return true;
        }

        /**
         * Tell if this array is lower, equal or greater in the lexicographical ordering
         * with respect to the specified array.
         *
         * @param      other other array
         * @return     <code>-1</code> if this array is lower, <code>0</code> if it is equal,
         *             <code>1</code> if it is greater in the ordering
         */

        public int compareTo(Object other){
            if (other == null) return 1;
            IntVector oth = (IntVector)other;
            int n = this.length;
            if (oth.length < n) n = oth.length;
            for (int i = 0; i < n; i++){
                int a1 = this.arr[i];
                int a2 = oth.arr[i];
                if (a1 != a2) return a1 - a2;
            }
            return this.length - oth.length;
        }

        /**
         * Deliver an array that contains the same values and in the same ordering as
         * the ones contained in this array.
         *
         * @return     array
         */

        int[] toArray(){
            int[] res = Arrays.copyOf(this.arr,this.length);
            return res;
        }

        /**
         * Deliver a copy of this object.
         *
         * @return     copy
         */

        IntVector copy(){
            IntVector res = new IntVector();
            res.arr = Arrays.copyOf(this.arr,this.length);
            res.length = this.length;
            return res;
        }

    }

    // ---------- Combvectors -----------------

    /**
     * Compressed representation of sparse matrices. This is a simple implementation
     * of a class that actually compresses them.
     */

    static class CombVector
    {
        /** Holes accessed mode. */
        static final int HOLES_ACCESSED = 1;

        /** Fold rows mode. */
        static final int FOLD_ROWS = 2;

        /** Input rows in (index,value) pairs format mode. */
        static final int PAIRS = 4;

        /** The comb-vector mode. */
        public int mode;

        /** The comb-vector merge table. */
        public int[] tabMerged;

        /** The comb-vector base table. */
        public int[] base;

        /** The comb-vector check table. */
        public int[] check;

        /** The value which is considered the hole. */
        public int holeValue;

        /** The size. */
        public long size;

        /**
         * Construct a new <codeCombVector></code> with the specified hole value and mode.
         *
         * @param      hole hole value
         * @param      mode mode
         */

        CombVector(int hole, int mode){
            this.holeValue = hole;
            this.mode = mode;
        }

        /**
         * Compress the specified matrix.
         *
         * @param      tabs matrix
         */

        void merge(int[][] tabs){
            int len = 0;
            for (int i = 0; i < tabs.length; i++){
                len += tabs[i][0];
            }
            this.base = new int[tabs.length];
            this.check = new int[len];
            this.tabMerged = new int[len];
            Arrays.fill(this.base,-1);
            Arrays.fill(this.check,-1);
            Arrays.fill(this.tabMerged,this.holeValue);
            int loc = 0;
            for (int i = 0; i < tabs.length; i++){
                this.base[i] = loc;
                for (int j = 1; j < tabs[i].length; j++){
                    int k = tabs[i][j++];                // index
                    this.tabMerged[k+loc] = tabs[i][j];  // value
                    this.check[k+loc] = loc;
                }
                loc += tabs[i][0];
                this.size += (tabs[i].length - 1) / 2;   // supposing max compression
            }            
        }

        /**
         * Trace the statistics of the compression.
         *
         * @param      tabs matrix
         */

        void statistics(){
        }
    }

    /** A compressed table. */

    class ComprTable {

        /** The compacted table. */
        int[] mergetable;

        /** The check table. */
        int[] check;

        /** The base table. */
        int[] base;

        /** The number of rows. */
        int rowsnr;

        /** The number of columns. */
        int colsnr;

        /** The size. */
        long size;

        /** The char column index type. */
        static final int T_CHAR = 0;

        /** The int column index type. */
        static final int T_INT = 2;

        /** The kind of column indexes. */
        int colKind;

        /** The values of holes. */
        int holeValue;

        /** The comb vector. */
        CombVector comb;

        /**
         * Construct this object.
         *
         * @param      comb comb vector
         * @param      rows number of rows
         * @param      cols number of columns
         * @param      type type of column indexes
         */

        ComprTable(CombVector comb, int rows, int cols, int type){
            this.mergetable = comb.tabMerged;
            this.check = comb.check;
            this.base = comb.base;
            this.rowsnr = rows;
            this.colsnr = cols;
            this.size = comb.size;
            this.colKind = type;
            this.holeValue = comb.holeValue;
            this.comb = comb;
        }

        /**
         * Deliver a string representing the cell of this compressed table
         * at the specified indexes
         *
         * @param      row row index
         * @param      col column index
         * @return     string
         */

        private String cellToString(int row, int col){
            StringBuilder str = new StringBuilder();
            int bas = this.base[row];
            int start = bas+col;
            int ele = 0;
            if ((this.comb.HOLES_ACCESSED & this.comb.mode) != 0){
                ele = this.check[start] == bas ? this.mergetable[start] : this.holeValue;
                if (ele == this.holeValue) return null;
            } else {
                ele = this.mergetable[start];
            }
            return str.append(ele).toString();
        }

        /**
         * Trace this table
         */

        void trace(){
            for (int i = 0; i < this.rowsnr; i++){
                Trc.out.printf("%s:",i);
                String sep = " ";
                for (int j = 0; j < this.colsnr; j++){
                    String cell = cellToString(i,j);
                    if (cell != null){
                        String col = null;
                        switch (this.colKind){
                        case T_CHAR: col = "" + (char)j; break;
                        case T_INT:  col = Integer.toString(j); break;
                        }
                        Trc.out.printf("%s%s: %s",sep,col,cell);
                        sep = "; ";
                    }
                }
                Trc.out.printf("\n");
            }
        }
    }

    // ---------- Symbols -----------------

    // Kinds of Symbols

    /* The symbols with kind >= S_CHAR denote characters; and may have a symset and optionally
     * a cset.
     */

    /** The kind of symbol for no symbol. */
    private static final int S_NONE = 0;

    /** The kind of symbol for a tag. */
    private static final int S_TAG = 1;

    /** The kind of symbol for a priority. */
    private static final int S_PRIO = 2;

    /** The kind of symbol for a single character. */
    private static final int S_CHAR = 3;

    /** The kind of symbol for the character set denoted by dot. */
    private static final int S_DOT = 4;

    /** The kind of symbol for a character set. */
    private static final int S_SET = 5;

    /** The kind of symbol for a negated character set. */
    private static final int S_NSET = 6;

    /** The kind of symbol for a set of subsets of classes. */
    private static final int S_CSET = 7;

    /** A representation of the symbol kinds. */
    private static final String[] SYM_KINDS = new String[]{"","t","p","",".","","",""};

    /** A symbol that represents input characters, tags and priorities. */

    class Symbol {

        /** The kind of symbol. */
        int kind = S_NONE;

        /** The symbol if the kind is character. */
        char sym;

        /** The set of symbols, if the symbol is a set. */
        boolean[] symset;

        /** The tag number if the symbol is a tag. */
        int tag;

        /** The priority if the symbol is a priority. */
        int prio;

        /** The set of classes, if the symbol is a set of classes. */
        boolean[] cset;

        /**
         * Deliver a string representing this symbol.
         *
         * @return     String
         */

        public String toString(){
            String str = "";
            switch (this.kind){
            case S_NONE:
                break;
            case S_CHAR:
                str += this.sym;
                break;
            case S_DOT:
                str += '.';
                break;
            case S_SET:
            case S_NSET:
                str += '[';
                boolean pos = true;
                if (this.kind == S_NSET){
                    str += "^";
                    pos = false;
                }
                str += symSetToString(this.symset,pos);
                str += ']';
                break;
            case S_TAG:
                str += this.tag;
                break;
            case S_PRIO:
                str += this.prio;
                break;
            case S_CSET:
                boolean first = true;
                for (int i = 0; i < this.cset.length; i++){
                    if (!this.cset[i]) continue;
                    if (!first) str += ", ";
                    first = false;
                    str += symClassTable[i].toString();
                }
                if (str.length() > 1){
                    str = '[' + str + ']';
                }
                break;
            }
            return str;
        }

        /**
         * Tell if the specified symbol is equal to this one.
         *
         * @param      other symbol
         */

        public boolean equals(Symbol other){
            if (other == null) return false;
            return this.kind == other.kind && this.sym == other.sym &&
                this.tag == other.tag && this.prio == other.prio &&
                Arrays.equals(this.symset,other.symset) &&
                Arrays.equals(this.cset,other.cset);
        }
    }

    /**
     * Deliver a new <code>Symbol</code> representing the specified character.
     *
     * @param      c character
     * @return     symbol
     */

    private Symbol newSymbolChar(char c ){
        Symbol res = new Symbol();
        res.kind = S_CHAR;
        res.sym = c;
        return res;
    }

    /**
     * Deliver a new <code>Symbol</code> representing the specified tag.
     *
     * @param      t tag
     * @return     symbol
     */

    private Symbol newSymbolTag(int t ){
        Symbol res = new Symbol();
        res.kind = S_TAG;
        res.tag = t;
        return res;
    }

    /**
     * Deliver a new <code>Symbol</code> representing the specified priority.
     *
     * @param      p priority
     * @return     symbol
     */

    private Symbol newSymbolPrio(int p ){
        Symbol res = new Symbol();
        res.kind = S_PRIO;
        res.prio = p;
        return res;
    }

    // ---------- AST's -----------------

    // kinds of AST nodes

    /** The kind of an AST node for a leaf. */
    private static final int A_LEA = 0;

    /** The kind of an AST node for an alternative. */
    private static final int A_ALT = 1;

    /** The kind of an AST node for a concatenation. */
    private static final int A_CON = 2;

    /** The kind of an AST node for a group. */
    private static final int A_GRO = 3;

    /** The kind of an AST node for the empty string. */
    private static final int A_EMP = 4;

    /** The kind of an AST node for the empty set. */
    private static final int A_NUL = 5;

    /** The strings representing the kinds of AST node. */
    private static final String[] astIcon = new String[]{
        "\u03a3",  // sigma
        "|",
        "\u2219",  // bullet
        "()",      // group
        "\u03b5",  // epsilon
        "\u03a6"}; // phi

    // kinds for groups

    /** The group kind of an AST node for the normal () group. */
    private static final int G_GRO = 0;

    /** The group kind of an AST node for the optional ()? group. */
    private static final int G_OPT = 1;

    /** The group kind of an AST node for the Kleene ()* group. */
    private static final int G_RE0 = 2;

    /** The group kind of an AST node for the positive ()+ group. */
    private static final int G_RE1 = 3;

    /** The group kind of an AST node for the interval (aka bounded) groups. */
    private static final int G_RE2 = 4;

    /** String representing group kinds. */
    private static final String[] groupKindStr = new String[]{
        "GRO","OPT","RE0","RE1","RE2"};

    /** Strings representing group symbols in RE strings. */
    private static final String[] groupSym = new String[]{
        "","?","*","+",""};

    /** String representing of capturing groups. */
    private static final String[] groupIconC = new String[]{
        "()","()?","()*","()+","(){}"};

    /** String representing of non-capturing groups. */
    private static final String[] groupIconN = new String[]{
        "()","?","*","+","{}"};

    /**
     * Deliver a string representing the group of the specified AST in compact form.
     *
     * @param      ast reference to the AST
     * @return     String
     */

    private String groupIcon(AstNode ast){
        if (this.astGroups != AST_GROUPS_ALL){
            return ast.isCapturing ? groupIconC[ast.groupKind] : groupIconN[ast.groupKind];
        }
        return groupIconC[ast.groupKind];
    }

    /**
     * Deliver a string representing the kind of the specified AST in compact form.
     *
     * @param      ast reference to the AST
     * @return     String
     */

    private String astKindString(AstNode ast){
        String str = astIcon[ast.kind];
        if (ast.kind == A_GRO){
            str = groupIcon(ast);
        }
        if (ast.altnr != 0) str += " #|" + ast.altnr;
        return str;
    }

    private int otag(AstNode ast){
        if (this.autotags) return ast.seq*2 + 1;
        return ast.implicit*2 - 1;
    }
    private int ctag(AstNode ast){
        if (this.autotags) return ast.seq*2 + 2;
        return ast.implicit*2;
    }
    private int ntag(AstNode ast){
        if (this.autotags) return -ast.seq*2 - 1;
        return 1 - ast.implicit*2;
    }
    private int cntag(AstNode ast){
        if (this.autotags) return -ast.seq*2 - 2;
        return - ast.implicit*2;
    }


    /** An AST node, representing a subexpression. */

    class AstNode {

        /** The serial number. */
        int seq;

        /** The reference to the brother. */
        AstNode bro;

        /** The reference to the son. */
        AstNode son;

        /** The reference to the father. */
        AstNode fat;

        /** The kind of node. */
        int kind;

        /** The symbol if the kind is leaf. */
        Symbol sym;

        /** The kind of group (if group). */
        int groupKind;

        /** The lower bound of the bounded group. */
        int lowerbound;

        /** The upper bound of the bounded group (-1 = infinite, 0 = none). */
        int upperbound;

        /** The position: sequence of indexes of level numbering. To show the LST only. */
        int pos;
        /** The index in the RE as string. */
        int cursor;

        /** The number of alternative (when this node is an alternative). */
        int altnr;

        /** Whether it is a capturing node. */
        boolean isCapturing;

        /** The level in the AST tree. */
        int lev;

        /** The implicit submatch index. */
        int implicit;

        /** The number of explicit (capturing) groups. */
        int explicit;

        /**
         * Deliver a string representing this node.
         *
         * @return     String
         */

        public String toString(){
            String str = "ast seq: " + this.seq;
            if (this.isCapturing) str += " capt";
            str += " pos:";
            str += posToString(this.pos);
            str += " ";
            if (this.altnr != 0) str += "|" + this.altnr + " ";
//            str += " " + astKindString(this);
            str += " " + (this.kind == A_GRO ? groupIcon(this) : astIcon[this.kind]);
            if (this.sym != null && this.kind == A_LEA){
                str += SYM_KINDS[this.sym.kind] + this.sym.toString();
            }
            str += " at: ";
            str += this.cursor;
            if (this.bro != null){
                str += " bro: ";
                str += this.bro.seq;
            }
            if (this.son != null){
                str += " son: ";
                str += this.son.seq;
            }
            if (this.fat != null){
                str += " fat: ";
                str += this.fat.seq;
            }
            str += " imp: " + this.implicit;
            str += " exp: " + this.explicit;
            return str;
        }

        /**
         * Deliver a string representing the tree of this node.
         *
         * @return     String
         */

        public String toTree(){
            StringBuilder sb = new StringBuilder();
            toTree(sb,this);
            return sb.toString();
        }
        public void toTree(StringBuilder sb, AstNode ast){
            sb.append("<");
            switch (ast.kind){
            case A_LEA: sb.append(ast.sym.toString()); break;
            case A_ALT: sb.append("|"); break;
            case A_CON: sb.append("∙"); break;
            case A_GRO: sb.append(groupIcon(ast)); break;
            case A_EMP: sb.append("ε"); break;
            case A_NUL: sb.append("Φ"); break;
            }
            sb.append("[");
            sb.append(ast.implicit);
            sb.append(",");
            sb.append(ast.explicit);
            sb.append("]");
            for (AstNode a = ast.son; a != null; a = a.bro){
                if (a != ast.son) sb.append(",");
                toTree(sb,a);
            }
            sb.append(">");
        }

        /**
         * Deliver a string representing the RE rooted in this node.
         *
         * @return     String
         */

        public String toRE(){
            StringBuilder sb = new StringBuilder();
            toRE(sb);
            return sb.toString();
        }

        /**
         * Append to the specified string builder a string representing the RE rooted
         * in this node.
         *
         * @param      sb string builder
         * @return     String
         */

        public void toRE(StringBuilder sb){
            if (this.kind == A_LEA){          // leaf
                if (this.sym.kind == S_TAG) addSpace(sb);
                sb.append(this.sym.toString());
            } else if (this.kind == A_ALT){   // alt
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i != this.son) sb.append("|");
                    if (i.kind == A_ALT){
                        sb.append("(");
                    }
                    i.toRE(sb);
                    if (i.kind == A_ALT){
                        sb.append(")");
                    }
                }
            } else if (this.kind == A_CON){   // conc
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append("(");
                    }
                    i.toRE(sb);
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append(")");
                    }
                }
            } else if (this.kind == A_EMP){   // empty
                sb.append("\u03b5");
            } else if (this.kind == A_NUL){   // empty set
                sb.append("\u03a6");
            } else {                          // group
                sb.append("(");
                if (this.son != null){
                    this.son.toRE(sb);
                    sb.append(")");
                }
                sb.append(groupSym[this.groupKind]);
                if (this.groupKind == G_RE2){
                    sb.append("{");
                    sb.append(this.lowerbound);
                    if (this.upperbound < 0){
                        sb.append(",");
                    } else if (this.upperbound > 0){
                        sb.append(",");
                        sb.append(this.upperbound);
                    }
                    sb.append("}");
                }
            }
        }

//-----------
        public void toGram(StringBuilder sb){
            if (this.kind == A_LEA){          // leaf
                if (this.sym.kind == S_TAG) addSpace(sb);
                sb.append(this.sym.toString());
            } else if (this.kind == A_ALT){   // alt
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i != this.son) sb.append("|");
                    if (i.kind == A_ALT){
                        sb.append("{");
                    }
                    i.toGram(sb);
                    if (i.kind == A_ALT){
                        sb.append("}");
                    }
                }
            } else if (this.kind == A_CON){   // conc
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append("{");
                    }
                    if (i != this.son) sb.append(" ");
                    i.toGram(sb);
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append("}");
                    }
                }
            } else if (this.kind == A_EMP){   // empty
                sb.append("\"\"");
            } else if (this.kind == A_NUL){   // empty set
                sb.append("\u03a6");
            } else {                          // group
                if (this.groupKind == G_OPT){
                    sb.append("[");
                    if (this.son != null){
                        this.son.toGram(sb);
                    }
                    sb.append("]");
                    return;
                }
                sb.append("{");
                if (this.son != null){
                    this.son.toGram(sb);
                    sb.append("}");
                }
                sb.append(groupSym[this.groupKind]);
                if (this.groupKind == G_RE2){
                    sb.append("(");
                    sb.append(this.lowerbound);
                    if (this.upperbound < 0){
                        sb.append(":");
                    } else if (this.upperbound > 0){
                        sb.append(":");
                        sb.append(this.upperbound);
                    }
                    sb.append(")");
                }
            }
        }

//-----------
        /**
         * Deliver a string representing the TRE rooted in this node, where the tags
         * are the ones that enclose each subexpression, a couple for each, with
         * consecutive numbers, which are the sequence number and the next to it for
         * each node.
         *
         * @return     String
         */

        public String toTRE(){
            StringBuilder sb = new StringBuilder();
            toTRE(sb,false);
            return sb.toString();
        }

        /**
         * Deliver a string representing the X(TRE(re)), i.e. the X operator that adds
         * negative tags to a TRE.
         *
         * @return     String
         */

        public String toXTRE(){
            StringBuilder sb = new StringBuilder();
            toTRE(sb,true);
            return sb.toString();
        }

        /**
         * Append a space if the last character of the specified string is numeric.
         *
         * @param      sb string
         */

        private void addSpace(StringBuilder sb){
            if (sb.length() == 0) return;
            char c = sb.charAt(sb.length()-1);
            if ('0' <= c && c <= '9') sb.append(" ");
        }

        /**
         * Append a string to the specified one representing the TRE rooted in this node,
         * where the tags are the ones that enclose each subexpressions, a couple for each,
         * with consecutive numbers, which are the sequence number and the next to it for
         * each node.
         *
         * @param      sb string
         * @param      neg <code>true</code> to add negative tags, <code>false</code> otherwise
         */

        private void toTRE(StringBuilder sb, boolean neg){
            addSpace(sb);
            if (ReTdfa.this.autotags || this.implicit != 0){
                sb.append(otag(this));
            }
            boolean fewNegTags = false;
            if (subhist){
                fewNegTags = okui && tagless && !finreg && negtags;
            } else {
                fewNegTags = okui && negtags;
            }
            doit: if (this.kind == A_LEA){    // leaf
                sb.append(this.sym.toString());
            } else if (this.kind == A_ALT){   // alt
                sb.append("(");
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i != this.son) sb.append("|");
                    if (i.kind == A_ALT){
                        sb.append("(");
                    }
                    if (subhist){
                        if (negtags && (autotags || this.son.implicit != 0)){
                            for (AstNode j = this.son; j != i; j = j.bro){
                                if (!areNegTags(j)) continue;
                                if (fewNegTags){
                                    // add the top opening negative tags for the preceding alternatives
                                    sb.append(ntag(j));
                                } else {
                                    negTagsToString(j,sb);   // add all negative tags
                                }
                            }
                        }
                    } else {
                        if (okui && neg){
                            // if there are tags in the preceding alternatives, then put them here negated
                            for (AstNode j = this.son; j != i; j = j.bro){
                                if (areNegTags(j)){
                                    sb.append(ntag(j));
                                }
                            }
                        }
                    }
                    i.toTRE(sb,neg);
                    if (subhist){
                        if (!okui || !tagless || finreg){
                            if (negtags && (autotags || this.son.implicit != 0)){
                                for (AstNode j = i.bro; j != null; j = j.bro){
                                    negTagsToString(j,sb);   // add all negative tags
                                }
                            }
                        }
                    } else {
                        if (okui && neg){
                            // if there are tags in the following alternatives, then put them here negated
                            for (AstNode j = i.bro; j != null; j = j.bro){
                                if (areNegTags(j)){
                                    sb.append(ntag(j));
                                }
                            }
                        } else {
                            if (neg && areNegTagsExcl(this,i)){
                                negTagsToStringExcl(this,i,sb);   // add negative tags
                            }
                        }
                    }
                    if (i.kind == A_ALT){
                        sb.append(")");
                    }
                }
                sb.append(")");
            } else if (this.kind == A_CON){   // conc
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append("(");
                    }
                    i.toTRE(sb,neg);
                    if (i.kind == A_ALT || i.kind == A_CON){
                        sb.append(")");
                    }
                }
            } else if (this.kind == A_EMP){   // empty
                sb.append("\u03b5");
            } else if (this.kind == A_NUL){   // empty set
                sb.append("\u03a6");
            } else {                          // group
                sb.append("(");
                int grkind = this.groupKind;
                if (this.son != null){
                    if (neg && areNegTags(this.son)){
                        switch (this.groupKind){
                        case G_OPT:
                            this.son.toTRE(sb,neg);
                            sb.append("|");
                            if (fewNegTags){
                                sb.append(ntag(this.son));
                            } else {
                                negTagsToString(this.son,sb);   // add negative tags
                            }
                            sb.append(")");
                            break doit;
                        case G_RE0:
                            this.son.toTRE(sb,neg);
                            sb.append(")*|(");
                            if (fewNegTags){
                                sb.append(ntag(this.son));
                            } else {
                                negTagsToString(this.son,sb);   // add negative tags
                            }
                            sb.append(")");
                            break doit;
                        case G_RE1:
                            this.son.toTRE(sb,neg);
                            sb.append(")+");
                            break doit;
                        case G_RE2:
                            if (this.lowerbound == 0){          // {0,m}
                                this.son.toTRE(sb,neg);
                                sb.append("){1,");
                                sb.append(this.upperbound);
                                sb.append("}|(");
                                if (fewNegTags){
                                    sb.append(ntag(this.son));
                                } else {
                                    negTagsToString(this.son,sb);   // add negative tags
                                }
                                sb.append(")");
                                break doit;
                            }
                            this.son.toTRE(sb,neg);
                            break;
                        default:
                            this.son.toTRE(sb,neg);
                        }
                    } else {
                        this.son.toTRE(sb,neg);
                    }
                    sb.append(")");
                }
                sb.append(groupSym[grkind]);
                if (this.groupKind == G_RE2){
                    sb.append("{");
                    sb.append(this.lowerbound);
                    if (this.upperbound < 0){
                        sb.append(",");
                    } else if (this.upperbound > 0){
                        sb.append(",");
                        sb.append(this.upperbound);
                    }
                    sb.append("}");
                }
            }
            addSpace(sb);
            if (ReTdfa.this.autotags || this.implicit != 0){
                sb.append(ctag(this));
            }
        }

        /**
         * Append to the specified string the negative tags corresponding to the ones
         * present in the asts rooted in the specified one excluding the specified node.
         *
         * @param      ast reference to the root AST
         * @param      excl reference to the AST to exclude
         * @param      sb string
         */

        private void negTagsToStringExcl(AstNode ast, AstNode excl, StringBuilder sb){
            for (AstNode i = ast.son; i != null; i = i.bro){
                if (i == excl) continue;
                negTagsToString(i,sb);
            }
        }

        /**
         * Append to the specified string the negative tags corresponding to the ones
         * present in the specified asts.
         *
         * @param      ast reference to the root AST
         * @param      sb string
         */

        private void negTagsToString(AstNode ast, StringBuilder sb){
            if (subhist){
                IntVector ntags = new IntVector();
                addNegTags(nfa,ast,ntags);
                for (int i = 0; i < ntags.size(); i++){
                    int tag = ntags.get(i);
                    sb.append(tag);
                }
                return;
            }
            int sp = 0;
            AstNode[] stack = new AstNode[10];
            stack[sp++] = ast;                        // push it
            // count the nodes
            int nrNodes = 0;
            while (sp > 0){                           // while stack not empty
                AstNode n = stack[--sp];              // pop
                nrNodes++;
                for (AstNode a = n.son; a != null; a = a.bro){
                    if (sp >= stack.length){
                        stack = Arrays.copyOf(stack,sp+10);
                    }
                    stack[sp++] = a;                  // push it
                }
            }
            // then generate the tags
            stack[sp++] = ast;                        // push it
            while (sp > 0){                           // while stack not empty
                AstNode n = stack[--sp];              // pop
                sb.append(ntag(n));
                for (AstNode a = n.son; a != null; a = a.bro){
                    sp++;                             // reserve space
                }
                int p = sp;
                for (AstNode a = n.son; a != null; a = a.bro){
                    stack[--p] = a;                   // push it
                }
            }
        }

        private void getMaxIndexes(AstNode ast, int[] idx){
            if (ast.implicit > idx[0]) idx[0] = ast.implicit;
            if (ast.explicit > idx[1]) idx[1] = ast.explicit;
            for (AstNode a = ast.son; a != null; a = a.bro){
                getMaxIndexes(a,idx);
            }
        }
        private String toIRE(){
            StringBuilder sb = new StringBuilder();
            int[] idx = new int[]{0,0};
            getMaxIndexes(this,idx);
            sb.append("(");
            // max implicit+1
            // max explicit+1
            sb.append(idx[0]);
            sb.append(",");
            sb.append(idx[1]);
            toIRE1(sb);
            sb.append(")");
            return sb.toString();
        }
        private void toIRE1(StringBuilder sb){
            sb.append("(");
            sb.append(this.implicit);
            sb.append(",");
            sb.append(this.explicit);
            if (this.kind == A_LEA){    // leaf
                sb.append(this.sym.toString());
            } else if (this.kind == A_ALT){   // alt
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i != this.son) sb.append("|");
                    i.toIRE1(sb);
                }
            } else if (this.kind == A_CON){   // conc
                for (AstNode i = this.son; i != null; i = i.bro){
                    if (i != this.son) sb.append("\u00b7");
                    i.toIRE1(sb);
                }
            } else if (this.kind == A_EMP){   // empty
                sb.append("\u03b5");
            } else if (this.kind == A_NUL){   // empty set
                sb.append("\u03a6");
            } else {                          // group
                this.son.toIRE1(sb);
            }
            sb.append(")");
            if (this.kind == A_GRO){          // group
                sb.append("<sup>");
                switch (this.groupKind){
                case G_GRO:
                    sb.append("1,1");
                    break;
                case G_OPT:
                    sb.append("0,1");
                    break;
                case G_RE0:
                    sb.append("0,\u221e");
                    break;
                case G_RE1:
                    sb.append("1,\u221e");
                    break;
                case G_RE2:
                    if (this.lowerbound == 0){          // {0,m}
                        sb.append("0,");
                        sb.append(this.lowerbound);
                    } else if (this.upperbound < 0){
                        sb.append(this.lowerbound);
                        sb.append(",\u221e");
                    } else {
                        sb.append(this.lowerbound);
                        sb.append(",");
                        sb.append(this.upperbound);
                    }
                }
                sb.append("</sup>");
            }
        }
    }

    /**
     * Deliver a string representing the specified character set using the bracketed
     * representation if it is a set.
     *
     * @param      symset set (array)
     * @param      pos <code>true</code> if the elements that are true in the array
     *             represent characters that are in the set, <code>false</code> if such
     *             elements represent character that are not in the set
     */

    private static String symSetToString(boolean[] arr, boolean pos){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.length; i++){
            if (arr[i] != pos) continue;
            if ((i < ' ') || (i > '~')){      // not printable
                sb.append(i);
            } else {
                sb.append((char)i);
            }
            int j = i;
            for (i++; i < arr.length; i++){
                if (arr[i] != pos) break;
            }
            if (i > j+2){                     // range (not of single character)
                sb.append("-");
                int n = i-1;
                if ((n < ' ') || (n > '~')){  // not printable
                    sb.append(n);
                } else {
                    sb.append((char)n);
                }
            } else if (i == j+2){     // range of single character
                i -= 2;
            } else {
                i--;
            }
        }
        return sb.toString();
    }

    /**
     * Deliver a string representing the specified position.
     *
     * @param      pos reference to the position
     * @return     string
     */

    private String posToString(int pos){
        return astPosToString(pos);
    }
    /** Sequence number of ast nodes. */
    private int astSeq;

    /** Map from integers to ast nodes. */
    private AstNode[] astMap;

    /**
     * Deliver a new AST node with the specified kind.
     *
     * @param      kind kind
     * @return     reference to the node
     */

    private AstNode newAstNode(int kind){
        AstNode node = new AstNode();
        node.kind = kind;
        node.cursor = this.startToken;
        node.seq = this.astSeq++;
        return node;
    }

    /**
     * Trace the subtree rooted in the specified ast.
     *
     * @param      ast reference to the AST node
     */

    private void traceAst(AstNode ast){
        for (AstNode a = ast; a != null; a = a.bro){
            Trc.out.printf("node: %s\n",a);
            traceAst(a.son);
        }
    }

    /**
     * Visit all the nodes rooted in the specified one and set in them their position,
     * father and sequence number, ordered as the positions.
     *
     * @param      ast reference to the AST node
     * @param      pos reference to the position
     * @param      fat reference to the AST node father
     * @return     string
     */

    private void setPosAst(AstNode ast, AstNode fat){
        if (ast == null) return;
        ast.fat = fat;
        if (fat != null){
            ast.lev = ast.fat.lev + 1;
        }
        ast.seq = this.astSeq++;
        this.astMap[ast.seq] = ast;
        int n = 1;
        for (AstNode a = ast.son; a != null; a = a.bro){
            setPosAst(a,ast);
            n++;
        }
    }

    /** The trie of positions. */
    private int[] posTable;

    /** The table that tells for each tag the trie of the position of its ast. */
    private int[] tagPosTable;

    /** The table that tells for each tag the altnr of if its ast if alternative, -1 otherwise. */
    private int[] tagAltTable;

    /** The table that tells for each tag the kind of the corresponding ast node. */
    private int[] tagKindTable;

    private void buildAstPos(){
        this.posTable = new int[this.astMap.length*2];
        int pti = buildAstPos(this.astRoot,0,0,0);
        this.posTable[pti++] = 0;
        this.posTable[pti++] = Integer.MAX_VALUE;
        this.eofAst.pos = pti-2;
        int len = 0;
        if (this.autotags || this.astGroups == AST_GROUPS_ALL){
            len = this.astMap.length*2;
        } else {
            len = this.astenumi*2+1;
        }
        this.tagPosTable = new int[len];
        this.tagAltTable = new int[len];
        this.tagKindTable = new int[len];
        for (int i = 1; i < this.tagPosTable.length; i++){
            AstNode ast = this.astMap[this.tagAst[i]];
            this.tagPosTable[i] = ast.pos;
            this.tagAltTable[i] = (ast.fat != null && ast.fat.kind == A_ALT) ? ast.altnr : -1;
            this.tagKindTable[i] = astKindToDomType(ast);
        }
// a table that for each tag tells if the corresponding ast is the body of a group and
// another that tells the astnr for the ones that are sons of alt
// incremental !tagless, there is a need for the ast
    }
    private static int astKindToDomType(AstNode ast){
        return ast.kind + (ast.kind == A_GRO ? ast.groupKind+3 : 0);
    }

    private int buildAstPos(AstNode ast, int pos, int pti, int ptifat){
        if (ast == null) return pti;
        int thispti = pti;
        ast.pos = thispti;
        this.posTable[pti++] = ptifat;
        this.posTable[pti++] = pos;
        int n = 1;
        for (AstNode a = ast.son; a != null; a = a.bro){
            pti = buildAstPos(a,n,pti,thispti);
            n++;
        }
        return pti;
    }
    private String astPosToString(int t){
        if (t == 0) return "\u2227";
        StringBuilder sb = new StringBuilder();
        for (int i = t; i != 0; i = this.posTable[i]){
            if (sb.length() > 0) sb.insert(0,".");
            int pos = this.posTable[i+1];
            if (pos == Integer.MAX_VALUE){
                sb.insert(0,"$");
            } else {
                sb.insert(0,Integer.toString(pos));
            }
        }
        return sb.toString();
    }

    private String tagPosToString(int t){
        if (this.tagPosTable[t] == 0) return "\u2227";
        StringBuilder sb = new StringBuilder();
        for (int i = this.tagPosTable[t]; i != 0; i = this.posTable[i]){
            if (sb.length() > 0) sb.insert(0,".");
            int pos = this.posTable[i+1];
            if (pos == Integer.MAX_VALUE){
                sb.insert(0,"$");
            } else {
                sb.insert(0,Integer.toString(pos));
            }
        }
        return sb.toString();
    }
    /**
     * Compute the implicit indexes for the AST rooted in the specified AST node.
     *
     * @param      ast reference to the AST node
     */

    private void astMark(AstNode ast){
        if (this.astGroups == AST_GROUPS_GRO1 && ast.kind == A_GRO && ast.isCapturing){
             ast.son.implicit = 1;
        } else if (ast.isCapturing){
             ast.implicit = 1;
        }
        int imp = 0;
        for (AstNode a = ast.son; a != null; a = a.bro){
            astMark(a);
            if (a.implicit == 1){
                imp = 1;
            }
        }
        ast.implicit |= imp;
        if (imp != 0 && (ast.kind == A_ALT || ast.kind == A_CON)){
            for (AstNode a = ast.son; a != null; a = a.bro){
                a.implicit = imp;
            }
        }
    }
    
    /** The current value of the implicit index. */
    private int astenumi;

    /** The current value of the explicit index. */
    private int astenume;

    /**
     * Compute the implicit and explicit indexes for the AST rooted in the specified AST node.
     *
     * @param      ast reference to the AST node
     */

    private void astEnum(AstNode ast){
        if (ast == this.astMap[0]){
            this.astenumi = 0;
            this.astenume = 0;
        }
        if (ast.implicit != 0){
            ast.implicit = ++this.astenumi;
        }
        if (this.astGroups != AST_GROUPS_FOLDED){
            if (ast.explicit != 0) ast.explicit = ++this.astenume;
        }
        for (AstNode a = ast.son; a != null; a = a.bro){
            astEnum(a);
        }
    }

    /**
     * Compute the arrays of the heights of the AST nodes of the AST rooted in the
     * specified node. Compute also the map from tag numbers to AST nodes.
     *
     * @param      ast reference to the AST node
     */

    private void astHeight(AstNode ast){
        if (ast == this.astMap[0]){
            int len = 0;
            if (this.autotags || this.astGroups == AST_GROUPS_ALL){
                len = this.astMap.length*2;
            } else {
                len = this.astenumi*2+1;
            }
            this.tagHeight = new int[len];
            this.tagAst = new int[len];
        }
        if (this.autotags || this.astGroups == AST_GROUPS_ALL){
            int tag = otag(ast);
            this.tagHeight[tag] = ast.lev + 1;
            this.tagAst[tag] = ast.seq;
            tag = ctag(ast);
            this.tagHeight[tag] = ast.lev;
            this.tagAst[tag] = ast.seq;
        } else if (ast.implicit != 0){
            int tag = otag(ast);
            if (ast.fat != null){
                this.tagHeight[tag] = this.tagHeight[otag(ast.fat)] + 1;
            } else {
                this.tagHeight[tag] = 1;
            }
            this.tagAst[tag] = ast.seq;
            tag = ctag(ast);
            this.tagHeight[tag] = this.tagHeight[otag(ast)] - 1;
            this.tagAst[tag] = ast.seq;
        }
        for (AstNode a = ast.son; a != null; a = a.bro){
            astHeight(a);
        }
    }

    /**
     * Make all the nodes of the specified AST non-capturing and then make a random one
     * capturing. For benchmark purposes only.
     *
     * @param      ast reference to the AST node
     */

    private void astFire(AstNode ast){
        for (int i = 0; i < this.astMap.length; i++){
            this.astMap[i].implicit = 0;
            this.astMap[i].explicit = 0;
        }
        Random ran = new Random();
        int r = ran.nextInt(this.astMap.length);
        this.astMap[r].implicit = 1;
        this.astMap[r].explicit = 1;
        this.tagHeight = new int[3];
        this.tagAst = new int[]{0,r,r};
    }

    /** Wheter only one capturing subpattern is present. */
    private boolean onetag;


    // ---------- Syntax analysis of a RE -----------------

    /* Syntax
     *
     *  - the syntax of RE as reported in papers is not a good one for applications.
     *    E.g. where a RE is allowed, a single terminal or a concatenations can occur.
     *    An application must instead have only one thing, which can contain one or several
     *    elements. Something like, e.g.:
     *
     *           r -> alt {| alt}
     *           alt -> {factor}+
     *           factor -> terminal | (r) | (r)? | (r)+ | (r)* | (r){m [,[n]]} | set
     *           set -> "." | "[" {terminal | terminal "-" terminal}+ "]"
     *
     *  - when a RE is a single character, ?, +, * and {} can occur without parentheses.
     *  - conditions:
     *       {n}:    n > 0
     *       {n,m}:  n > m
     */

    /** Whether alternative operator is binary (otherwise n-ary). */
    private boolean altbin;

    /** Whether concatenation operator is binary (otherwise n-ary). */
    private boolean concbin;

    /** The reference to the current node. */
    private AstNode curNode; 

    /** The reference to the root of the AST. */
    private AstNode astRoot;

    /** The index in RE (as a string). */
    private int cursor;

    /** The index of the start of a token in RE (as a string). */
    private int startToken;

    /** The RE to be analysed. */
    private String re;

    /**
     * Build the AST from the specified string containing the RE.
     *
     * @param      re string
     * @return     reference to the root of the AST
     */

    private AstNode buildAst(String re){
        this.astGroups = AST_GROUPS_ALL;
        this.newTNFA = false;
//        if ((this.posix && !this.autotags) || this.onetag){
        if (this.posix && !this.autotags){
            this.astGroups = AST_GROUPS_GRO1;
            this.newTNFA = true;
        }
        return buildAst1(re);
    }

    private AstNode buildAst1(String re){
        this.re = re;
        this.astSeq = 0;
        this.error = false;

        this.cursor = 0;
        this.startToken = 0;
        this.curNode = null;
        expression();
        if (this.astGroups == AST_GROUPS_FOLDED){
            this.curNode.isCapturing = true;
            this.curNode.explicit++;
        } else if (this.astGroups == AST_GROUPS_GRO1){
        //    this.curNode.implicit = 1;
        //    this.curNode.explicit = 1;
        } else if (this.astGroups == AST_GROUPS_SEP){
            AstNode outer = newAstNode(A_GRO);
            outer.groupKind = G_GRO;
            outer.isCapturing = true;
            outer.explicit++;
            outer.cursor = this.curNode.cursor;
            outer.son = this.curNode;
            this.curNode = outer;
        }
        if (this.error || getsym() != -1){    // error or whole re not consumed
            return null;
        }

        AstNode ast = this.curNode;
        this.eofAst = newAstNode(A_LEA);
        this.eofAst.sym = newSymbolChar(EOF );         // eof
        this.astMap = new AstNode[this.astSeq];
        this.astSeq = 0;
        setPosAst(ast,null);
        if (this.astSeq+1 < this.astMap.length){      // there were spurious asts
            // System.out.printf("!! spurious asts %s %s\n",this.astSeq,this.astMap.length);
            this.astMap = new AstNode[this.astSeq];   // do it again
            this.astSeq = 0;
            setPosAst(ast,null);
        }
        this.astMap[this.eofAst.seq] = this.eofAst;
        if (this.astGroups != AST_GROUPS_ALL){
            astMark(ast);
            astEnum(ast);
        }
        if (this.onetag){
            astFire(ast);
        } else {
            astHeight(ast);
        }
        this.nrSubExpr = this.astMap.length-1;
        this.astRoot = ast;

        buildAstPos();
        /*
        for (int i = 0; i < this.astMap.length; i++){
            Trc.out.printf("ast %s\n",this.astMap[i]);
        }
        */
        return this.astRoot;
    }

    /** The AST representing the end of text. */
    private AstNode eofAst;

    /** The char representing the end of text. */
    private static final char EOF = '\u22a3';

    /** The height of each tag. */
    private int[] tagHeight;

    /** The map from tags to AST numbers. */
    private int[] tagAst;

    /** Whether an error has occurred. */
    private boolean error;

    /**
     * Parse an expression.
     */

    private void expression(){
        this.curNode = null;
        AstNode r = null;
        AstNode altnode = null;
        doit: {
            subexpression();                         // allow also nothing
            if (this.error) return;
            if (this.curNode == null){
                this.curNode = newAstNode(A_EMP);    // return empty
                this.curNode.sym = newSymbolChar('\u03b5' );
            }
            r = this.curNode;
            int n = 1;
            l: for (;;){
                gsep();
                int symv = getsym();
                char sym = (char)symv;
                if (symv < 0) break;
                if (sym != '|'){
                    this.cursor--;
                    break;
                }
                if (altnode == null){
                    altnode = newAstNode(A_ALT);
                    altnode.son = r;
                    r.altnr = n;
                }
                n++;
                subexpression();                           // alternative, require a term
                if (this.error) return;
                if (this.curNode == null){
                    this.curNode = newAstNode(A_EMP);      // return empty
                    this.curNode.sym = newSymbolChar('\u03b5' );
                }
                r.bro = this.curNode;                      // store anyway
                r = this.curNode;
                r.altnr = n;
                if (this.altbin){                          // generate binary alternatives
                    if (altnode.son.bro != null &&         // three sons present
                        altnode.son.bro.bro != null){
                        AstNode curaltnode = newAstNode(A_ALT);
                        curaltnode.son = altnode.son;
                        altnode.son = curaltnode;
                        curaltnode.son.bro.bro = null;
                        curaltnode.bro = this.curNode;
                    }
                }
            } // l;
        } // doit
        if (altnode != null){
            this.curNode = altnode;
        }
    }

    /**
     * Parse a subexpression.
     */

    private void subexpression(){
        this.curNode = null;
        factor();
        if (this.error) return;
        AstNode concnode = null;
        if (this.curNode != null){
            AstNode q = this.curNode;
            int n = 1;
            l: for (;;){
                AstNode p = this.curNode;
                n++;
                factor();
                if (this.error) return;
                if (this.curNode != null){    // several terms
                    if (concnode == null){
                        concnode = newAstNode(A_CON);
                        concnode.son = p;
                        q = p;
                    }
                } else {
                    this.curNode = p;
                    break;
                }
                q.bro = this.curNode;
                q = this.curNode;
            } // l
        }
        if (concnode != null){
            this.curNode = concnode;
            if (this.concbin){              // generate binary concatenations
                for (AstNode a = concnode.son; a != null;){
                    AstNode bro = a.bro;
                    if (bro.bro != null){      // not the last
                        AstNode c = newAstNode(A_CON);
                        c.son = bro;
                        a.bro = c;
                    } else {
                        break;
                    }
                    a = bro;
                }
            }

        }
    }

    /** Whether simple groups are not represented in the AST. */
    private boolean noGRO;

    /** The kind of representation for groups. */
    private int astGroups;

    /** Every construct is a capturing group. */
    private static int AST_GROUPS_ALL = 0;

    /** One node per (r), (r)*, etc. */
    private static int AST_GROUPS_ONE = 1;

    /** () folded. */
    private static int AST_GROUPS_FOLDED = 2;

    /** One node for () and one for *, etc. */
    private static int AST_GROUPS_SEP = 3;

    /** () as (){1}. */
    private static int AST_GROUPS_GRO1 = 4;

    /**
     * Parse a factor.
     */

    private void factor(){
        this.curNode = null;
        gsep();
        int symv = getsym();
        char sym = (char)symv;
        AstNode groupnode = null;
        doit: if (symv == -1){
            return;
        } else if (sym == '|' || sym == ')'){
            this.cursor--;
        } else if (sym == '('){
            expression();
            if (this.error) return;
            groupnode = newAstNode(A_GRO);
            groupnode.groupKind = G_GRO;
            groupnode.son = this.curNode;
            if (getsym() != ')'){
                this.error = true;
                return;
            }
            symv = getsym();
            sym = (char)symv;
            if (sym == '*'){
                groupnode.groupKind = G_RE0;
            } else if (sym == '+'){
                groupnode.groupKind = G_RE1;
            } else if (sym == '?'){
                groupnode.groupKind = G_OPT;
            } else if (sym == '{'){
                getbounds(groupnode);
                if (this.error){
                    return;
                }
            } else if (symv != -1){
                this.cursor--;
            }

            if (this.astGroups == AST_GROUPS_ONE){
                groupnode.isCapturing = true;
                groupnode.explicit = 1;
            } else if (this.astGroups == AST_GROUPS_FOLDED){
                if (groupnode.groupKind == G_GRO){
                    this.astSeq--;                     // simple group: discard
                    groupnode = this.curNode;
                    groupnode.isCapturing = true;
                    groupnode.explicit++;
                } else {
                    groupnode.son.isCapturing = true;
                    groupnode.son.explicit++;
                }
            } else if (this.astGroups == AST_GROUPS_SEP){
                if (groupnode.groupKind != G_GRO){
                    AstNode paren = newAstNode(A_GRO);
                    paren.son = groupnode.son;
                    groupnode.son = paren;
                    paren.isCapturing = true;
                    paren.explicit = 1;
                } else {
                    groupnode.isCapturing = true;
                    groupnode.explicit = 1;
                }
            } else if (this.astGroups == AST_GROUPS_GRO1){
                if (groupnode.groupKind == G_GRO){
                    groupnode.groupKind = G_RE2;
                    groupnode.lowerbound = 1;
                    groupnode.upperbound = 0;
                }
                groupnode.isCapturing = true;
                groupnode.son.explicit = 1;
            } else {
                groupnode.isCapturing = true;
            }
        } else if (sym == '['){                    // set
            this.curNode = newAstNode(A_LEA);
            this.curNode.sym = new Symbol();
            this.curNode.sym.kind = S_SET;
            this.curNode.sym.symset = new boolean[128];
            boolean first = true;
            int prev = -1;
            for (;;){
                symv = getsym();
                if (symv < 0 || symv > this.curNode.sym.symset.length){
                    this.error = true;
                    return;
                }
                sym = (char)symv;
                if (sym == ']') break;
                if (first){
                    if (sym == '^'){
                        this.curNode.sym.kind = S_NSET;
                        continue;
                    }
                    first = false;
                }
                if (sym == '-'){  // range
                    symv = getsym();
                    if (symv < 0 || symv > this.curNode.sym.symset.length){
                        this.error = true;
                        return;
                    }
                    sym = (char)symv;
                    if (sym == '-' || sym == ']'){
                        this.error = true;
                        return;
                    }
                    for (int j = prev+1; j <= symv; j++){
                        this.curNode.sym.symset[j] = true;
                    }
                } else {
                    this.curNode.sym.symset[symv] = true;
                }
                if (sym != '-') prev = symv;
            }
            if (this.curNode.sym.kind == S_NSET){
                for (int i = 0; i < this.curNode.sym.symset.length; i++){
                    this.curNode.sym.symset[i] = !this.curNode.sym.symset[i];
                }
            }
        } else if (sym == '.'){                    // dot
            this.curNode = newAstNode(A_LEA);
            this.curNode.sym = new Symbol();
            this.curNode.sym.kind = S_DOT;
            this.curNode.sym.sym = sym;
            if (this.dotset == null){
                this.dotset = new boolean[128];
                Arrays.fill(this.dotset,true);
                this.dotset['\n'] = false;
            }
            this.curNode.sym.symset = this.dotset;
        } else {
            if (sym == '\u03b5'){
                this.curNode = newAstNode(A_EMP);      // return empty
                this.curNode.sym = new Symbol();
                this.curNode.sym.kind = S_CHAR;
                this.curNode.sym.sym = sym;
                break doit;
            }
            if (sym == '\u03a6'){
                this.curNode = newAstNode(A_NUL);      // return empty set
                this.curNode.sym = new Symbol();
                this.curNode.sym.kind = S_CHAR;
                this.curNode.sym.sym = sym;
                break doit;
            }
            if (('a' <= sym) && (sym <= 'z')){         // normal leaf
                this.curNode = newAstNode(A_LEA);
                this.curNode.sym = new Symbol();
                this.curNode.sym.kind = S_CHAR;
                this.curNode.sym.sym = sym;
            } else {                                   // tag
                boolean neg = false;
                if (sym == '-'){
                    neg = true;
                } else {
                    this.cursor--;
                }
                int tag = getint();
                if (tag <= 0){
                    this.error = true;
                    return;
                }
                if (neg) tag = -tag;
                this.curNode = newAstNode(A_LEA);
                this.curNode.sym = newSymbolTag(tag );
            }
        } // doit
        if (groupnode != null){
            this.curNode = groupnode;
        }
        for (;;){
            gsep();
            symv = getsym();
            sym = (char)symv;
            if (sym == '*'){
                groupnode = newAstNode(A_GRO);
                groupnode.groupKind = G_RE0;
                groupnode.son = curNode;
            } else if (sym == '+'){
                groupnode = newAstNode(A_GRO);
                groupnode.groupKind = G_RE1;
                groupnode.son = this.curNode;
            } else if (sym == '?'){
                groupnode = newAstNode(A_GRO);
                groupnode.groupKind = G_OPT;
                groupnode.son = this.curNode;
            } else if (sym == '{'){                  // parse {n,m}
                groupnode = newAstNode(A_GRO);
                getbounds(groupnode);
                if (this.error){
                    return;
                }
            } else if (symv != -1){
                this.cursor--;
                break;
            } else {
                break;
            }
            this.curNode = groupnode;
        }
    }

    /** The set of characters represented by the dot */
//    private static boolean[] dotset;
    private boolean[] dotset;

    /**
     * Get the bounds of a bounded group.
     */

    private AstNode getbounds(AstNode groupnode){
        groupnode.groupKind = G_RE2;
        groupnode.son = this.curNode;
        // get the lower bound
        int bound = getint();
        if (bound < 0){                      // integer not found or illegal
            this.error = true;
            return null;
        }
        groupnode.lowerbound = bound;
        int symv = getsym();
        if (symv == -1){
            this.error = true;
            return null;
        }
        char sym = (char)symv;
        if (sym == '}'){                     // {n}
            groupnode.upperbound = 0;
            if (groupnode.lowerbound <= 0){
                this.error = true;
                return null;
            }
        } else if (sym == ','){
            symv = getsym();
            if (symv == -1){
                this.error = true;
                return null;
            }
            sym = (char)symv;
            if (sym == '}'){                 // {n,}
                groupnode.upperbound = -1;
                if (groupnode.lowerbound == 0){
                    groupnode.groupKind = G_RE0;
                } else if (groupnode.lowerbound == 1){
                    groupnode.groupKind = G_RE1;
                }
            } else {                         // {n,m}
                this.cursor--;
                // get the upper bound
                bound = getint();
                if (bound < 0){
                    this.error = true;
                    return null;
                }
                groupnode.upperbound = bound;
                if (groupnode.upperbound <= groupnode.lowerbound){
                    this.error = true;
                    return null;
                }
                symv = getsym();
                if (symv == -1){
                    this.error = true;
                    return null;
                }
                sym = (char)symv;
                if (sym != '}'){
                    this.error = true;
                    return null;
                }
            }
        } else {
            this.error = true;
            return null;
        }
        return groupnode;
    }

    /**
     * Get an integer >= 0.
     *
     * @return     value, -1 if not present
     */

    private int getint(){
        int res = 0;
        boolean found = false;
        for (;;){
            int cur = this.cursor;
            int symv = getsym();
            if (symv < 0) break;               // end of data
            if (this.cursor-cur > 1){          // number ended by spaces
                this.cursor--;
                break;
            }
            char c = (char)symv;
            if ((c < '0') || ('9' < c)){
                this.cursor--;
                break;
            }
            res *= 10;
            if (res > 0){
                found = false;
                break;
            }
            int digit = (int)c - '0';
            res -= digit;                     // use negative accumulators, ..
            if (res > 0){                     // .. which is larger than a ..
                found = false;                // .. positive one
                break;
            }
            found = true;
        }
        if (found){
            res = -res;
            if (res < 0){
                found = false;
            }
        }
        if (!found) res = -1;
        return res;
    }

    /**
     * Get the next character from the RE.
     *
     * @return     character, or -1 if no more available
     */

    private int getsym(){
        int res;
        for (; this.cursor < this.re.length(); this.cursor++){
             if (this.re.charAt(this.cursor) != ' ') break;
        }
        if (this.cursor >= this.re.length()){   // eof
            res = -1;
        } else {
            res = this.re.charAt(this.cursor++);
        }
        return res;
    }

    /**
     * Skip whitespaces.
     *
     * @return     character, or -1 if no more available
     */

    private void gsep(){
        for (; this.cursor < this.re.length(); this.cursor++){
             if (this.re.charAt(this.cursor) != ' ') break;
        }
        this.startToken = this.cursor;
    }

    /** A T-string. */

    /** The character representing the first tag. */
    private static final int T_TAG = 32768;

    /** The character representing the first negated tag. */
    private static final int T_NTAG = 49152;

    /** The character representing the first character class. */
    private static final int T_CLASS = 16384;

    /** A T-string. */

    private class Tstring implements Comparable {

        /** The string: tags are represented as characters in the upper half plane (upper quarter for the negative ones). */
        StringBuilder string;

        /**
         * Construct a new T-string.
         */

        Tstring(){
            this.string = new StringBuilder();
        }

        /**
         * Construct a new T-string as a copy of the specified one.
         *
         * @param      s T-string
         */

        Tstring(Tstring s ){
            this.string = new StringBuilder();
            if (s != null) this.string.append(s.string);
        }

        /**
         * Construct a new T-string containing a copy of the specified array.
         *
         * @param      a T-string array
         */

        Tstring(char[] a ){
            this.string = new StringBuilder();
            if (a != null){
                for (int i = 0; i < a.length; i++){
                    this.string.append(a[i]);
                }
            }
        }

        /**
         * Construct a new T-string containing a copy of the specified portion of array.
         *
         * @param      a T-string array
         * @param      len its length
         */

        Tstring(char[] a, int len ){
            this.string = new StringBuilder();
            if (a != null){
                for (int i = 0; i < len; i++){
                    this.string.append(a[i]);
                }
            }
        }

        /**
         * Construct a new T-string containing a copy of the specified portion of array.
         *
         * @param      a T-string array
         * @param      startg start index in it
         * @param      len its length
         */

        Tstring(char[] a, int start, int len ){
            this.string = new StringBuilder();
            if (a != null){
                for (int i = 0, j = start; i < len; i++){
                    this.string.append(a[j++]);
                }
            }
        }

        /**
         * Construct a new T-string converting the specified string. In it, "." is used
         * as separator, "-" is used to denote negative tags. The syntax is lenient:
         * multiple "." are allowed, "." is needed only to delimit numbers when not
         * delimited otherwise.
         *
         * @param      s string
         * @param      len length of the string
         */

        Tstring(String s, int len){
            this.string = new StringBuilder();
            for (int i = 0; i < len;){
                char c = s.charAt(i);
                if (c == '.' || c == ' '){
                    i++;
                    continue;
                }
                boolean neg = false;
                if (c == '-'){
                    neg = true;
                    if (i++ == s.length()) break;
                    c = s.charAt(i);
                }
                if ('0' <= c && c <= '9'){
                    int t = (int)(c - '0');
                    for (i++; i < s.length(); i++){
                        c = s.charAt(i);
                        if ('0' <= c && c <= '9'){
                            t *= 10;
                            t += (int)(c - '0');
                        } else {
                            break;
                        }
                    }
                    append(neg ? -t : t);
                } else {
                    append(c);
                    i++;
                }
            }
        }

        /**
         * Tell if the specified string is equal to this one.
         *
         * @param      other string
         */

        public boolean equals(Tstring other){
            if (other == null) return false;
            return other.string.toString().equals(this.string.toString());
        }

        /**
         * Compare this object with the specified one.
         *
         * @param      other the symbol to compare
         * @return     &lt; = or &gt; 0 if this object precedes, is equal or follows the other
         */

        public int compareTo(Object other){
            return this.string.toString().compareTo(((Tstring)other).string.toString());
        }

        /**
         * Deliver an integer representing the tag at the specified position in the string,
         * 0 if it is not a tag;
         *
         * @return     tag
         */

        public int getTag(int i){
            char c = this.string.charAt(i);
            if (c < T_TAG){
                return 0;
            }
            return charToTag(c);
        }

        /**
         * Deliver the character at the specified position.
         *
         * @return     tag
         */

        private char charAt(int i){
            return this.string.charAt(i);
        }

        /**
         * Deliver a string representing this T-string.
         *
         * @return     string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < this.string.length(); i++){
                char c = this.string.charAt(i);
                int tag = getTag(i);
                if (tag == 0){
                    if (c >= T_CLASS){
                        sb.append(symClassTable[c-T_CLASS].toString());
                    } else {
                        sb.append(c);
                    }
                } else if (tag > 0){
                    addSpace(sb);
                    sb.append(tag);
                } else {
                    sb.append("-");
                    sb.append(-tag);
                }
            }
            return sb.toString();
        }

        /**
         * Deliver a string representing this T-string in raw format.
         *
         * @return     string
         */

        public String toRaw(){
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < this.string.length(); i++){
                char c = this.string.charAt(i);
                if (i > 0) sb.append(" ");
                sb.append(Integer.toHexString(Character.getNumericValue(c)));
            }
            return sb.toString();
        }

        /**
         * Append a space if the last character of the specified string is numeric.
         *
         * @param      sb string
         */

        private void addSpace(StringBuilder sb){
            if (sb.length() == 0) return;
            char c = sb.charAt(sb.length()-1);
            if ('0' <= c && c <= '9') sb.append(" ");
        }

        /**
         * Append a character to this string.
         *
         * @param      c character
         */

        public void append(char c){
            this.string.append(c);
        }

        /**
         * Append a tag to this string.
         *
         * @param      t tag
         */

        public void append(int t){
            this.string.append(intToTag(t));
        }

        /**
         * Append a tstring to this string.
         *
         * @param      s tstring
         */

        public void append(Tstring s){
            if (s != null){
                this.string.append(s.string);
            }
        }

        /**
         * Append a character class to this string.
         *
         * @param      c class
         */

        public void appendClass(int c){
            this.string.append((char)(c + T_CLASS));
        }

        /**
         * Append a String to this string.
         *
         * @param      s String
         */

        public void append(String s){
            this.string.append(s);
        }

        /**
         * Append a tstring represented as an array to this string.
         *
         * @param      s array
         */

        public void append(char[] s){
            if (s != null){
                this.string.append(s);
            }
        }

        /**
         * Append a tstring represented as an array slice to this string.
         *
         * @param      s array
         * @param      start start offset
         * @param      end end offset
         */

        public void append(char[] s, int start, int end){
            if (s != null){
                this.string.append(s,start,end);
            }
        }

        /**
         * Deliver a new Tstring that contains the concatenation of this Tstring with the
         * specified one.
         *
         * @param      s String
         */

        public Tstring cat(Tstring s ){
            Tstring res = new Tstring();
            res.append(this);
            res.append(s);
            return res;
        }

        /**
         * Deliver the length of this tstring.
         *
         * @return     length
         */

        public int length(){
            return this.string.length();
        }

        /**
         * Deliver a new Tstring that is the substring of this one starting from the specified
         * start index (included) to the end.
         *
         * @para,      start start index
         * @return     Tstring
         */

        public Tstring substring(int start){
            Tstring res = new Tstring();
            res.string.append(this.string.substring(start));
            return res;
        }

        /**
         * Deliver a new Tstring that is the substring of this one starting from the specified
         * start index (included) to the specified end one (excluded);
         *
         * @param      start start index
         * @param      end end index
         * @return     Tstring
         */

        public Tstring substring(int start, int end){
            Tstring res = new Tstring();
            res.string.append(this.string.substring(start,end));
            return res;
        }

        /**
         * Deliver a string representing the code points of the elements of this Tstring.
         *
         * @return     string
         */

        public String toCodes(){
            String str = "";
            for (int i = 0; i < this.string.length(); i++){
                if (str.length() > 0) str += "  ";
                str += this.string.codePointAt(i);
            }
            return str;
        }

        /**
         * Empty this Tstring.
         */

        public void clear(){
            this.string.setLength(0);
        }

        /**
         * Copies the contents of this Tstring in the specified array.
         *
         * @param      dst destination array
         * @param      start index at which the contents is copied
         */

        void copy(char[] dst, int start){
            this.string.getChars(0,this.string.length(),dst,start);
        }
    }

    /**
     * Deliver the character representing the specified tag.
     *
     * @return     character
     */

    private static char intToTag(int t){
        char c = (char)(t + T_TAG);
        if (t < 0) c = (char)(-t + T_NTAG);
        return c;
    }

    /**
     * Deliver the tag represented by the specified character.
     *
     * @return     tag
     */

    private static int charToTag(char sym){
        if (sym >= T_NTAG){
            return -(sym - T_NTAG);
        } else if (sym >= T_TAG){
            return sym - T_TAG;
        }
        return 0;
    }


    /** A T-string trie implemented with a block array. */

    private class TstringTrie {

        /* This class contains a trie of elements. Each element is made of a pointer
         * (a block number and an offset), a length and a sequence of characters.
         * Each element (except for the first) points to another element. This allows
         * to store efficiently strings that share a common head.
         * A string is the sequence of characters in a chain of elements, and is denoted
         * by the index of the last element in the chain.
         */

        /** The directory of blocks. */
        char[][] dir;

        /** The number of the current block. */
        int curblock;

        /** The offset in the current block. */
        int curoffset;

        /** The current block. */
        char[] block;

        /** The size of blocks. */
//        private int BLOCK_SIZE = 1024;
        private int BLOCK_SIZE = 8192;

        /** The increment for the extension of the directory. */
        private int DIR_STEP = 1024;

        /** The number of chars in the whole trie. */
        long nchars;

        /**
         * Construct a new trie.
         */

        TstringTrie(){
            create();
        }

        /**
         * Construct a new trie.
         *
         * @param      ds directory step
         * @param      bs block size
         */

        TstringTrie(int ds, int bs){
            DIR_STEP = ds;
            BLOCK_SIZE = bs;
            create();
        }

        /**
         * Create the first block.
         */

        private void create(){
            this.dir = new char[DIR_STEP][];
            this.curblock = 0;
            this.block = new char[BLOCK_SIZE];
            this.dir[this.curblock] = this.block;
            this.curoffset = 0;                 // an empty string at beginning
            this.block[this.curoffset++] = 0;
            this.block[this.curoffset++] = 0;
            this.block[this.curoffset++] = 0;
            this.nchars = 0;
        }

        /**
         * Re-initialize this trie.
         */

        void init(){
            this.curblock = 0;
            this.curoffset = 3;
            this.block = this.dir[this.curblock];
            this.nchars = 0;
        }

        /**
         * Ensure that the current block has at least the specified number of characters
         * free.
         *
         * @param      length desired space
         */

        private void ensure(int length){
            if (length > BLOCK_SIZE){
                throw new IllegalArgumentException();
            }
            if (this.block.length - this.curoffset < length){
                // allocate a new block or reuse an existing one
                if (this.dir.length - this.curblock <= 1 ||
                    this.dir[this.curblock+1] == null){
                    this.block = new char[BLOCK_SIZE];
                    if (this.dir.length - this.curblock <= 1){
                        this.dir = Arrays.copyOf(this.dir,this.dir.length+DIR_STEP);
                    }
                    this.curblock++;
                    this.dir[this.curblock] = this.block;
                } else {
                    this.curblock++;
                    this.block = this.dir[this.curblock];
                }
                this.curoffset = 0;
            }
        }

        /**
         * Append the specified tstring to the specified trie element.
         *
         * @param      prev index of the trie element
         * @param      t tstring to be appended
         */

        int append(int prev, Tstring t){
            int len = t.length();
            this.nchars += len;
            ensure(len+3);
            int idx = (this.curblock << 16) | this.curoffset;
            this.block[this.curoffset++] = (char)(prev >> 16);
            this.block[this.curoffset++] = (char)(prev & 0xffff);
            int xxx = this.curoffset;
            this.block[this.curoffset++] = (char)len;
            for (int i = 0; i < len; i++){
                this.block[this.curoffset++] = t.charAt(i);
            }
            return idx;
        }

        /**
         * Deliver a tstring containing the concatenated characters of the chain of elements
         * whose tail is the specified one.
         *
         * @param      idx index of the tail
         * @return     Tstring
         */

        Tstring toTstring(int idx ){
            Tstring res = new Tstring();
            for (int i = idx; i > 0;){
                int blknr = i >> 16;
                int blkoff = i & 0xffff;
                char[] blk = this.dir[blknr];
                res.string.insert(0,blk,blkoff+3,blk[blkoff+2]);
                i = blk[blkoff] << 16 | blk[blkoff+1];
            }
            return res;
        }

        /**
         * Deliver the length of the concatenated characters of the chain of elements
         * whose tail is the specified one.
         *
         * @param      idx index of the tail
         */

        int length(int idx){
            int len = 0;
            for (int i = idx; i > 0;){
                int blknr = i >> 16;
                int blkoff = i & 0xffff;
                char[] blk = this.dir[blknr];
                len += blk[blkoff+2];
                i = blk[blkoff] << 16 | blk[blkoff+1];
            }
            return len;
        }

        /**
         * Copy the concatenated characters of the chain of elements whose tail is the
         * specified one into the specified array.
         *
         * @param      idx index of the tail
         * @param      dst array
         * @param      len number of characters in the chain
         */

        void copy(int idx, char[] dst, int len){
            for (int i = idx; i > 0;){
                int blknr = i >> 16;
                int blkoff = i & 0xffff;
                char[] blk = this.dir[blknr];
                len -= blk[blkoff+2];
                System.arraycopy(blk,blkoff+3,dst,len,blk[blkoff+2]);
                i = blk[blkoff] << 16 | blk[blkoff+1];
            }
        }

        /**
         * Trace this trie.
         */

        void trace(){
            for (int i = 0; i < this.dir.length; i++){
                char[] blk = this.dir[i];
                if (blk == null) break;
                for (int j = 0; j < blk.length;){
                    // check if there is a node here
                    if (blk.length - j < 3) break;
                    int len = blk[j+2];
                    if (j + 3 + len > blk.length) break;
                    // there are the pointer, the length and the chars
                    Tstring str = new Tstring();
                    str.append(blk,j+3,blk[j+2]);
                    Trc.out.printf("%s.%s: %s.%s %s\n",i,j,(int)blk[j],(int)blk[j+1],str);
                    j += 3 + len;
                }
            }
        }

        /**
         * Deliver the size of the used part of this tstring (including the unused part
         * of the blocks except for the last).
         * whose tail is the specified one.
         *
         * @return     size
         */

        int trieSize(){
            int size = 0;
            for (int i = 0; i < this.dir.length; i++){
                char[] blk = this.dir[i];
                if (blk == null) break;
                if (i < this.curblock){
                    size += (this.curoffset + 1) *2 + 4;
                } else {
                    size += blk.length *2 + 4;
                }
            }
            return size;
        }
    }
    /** Whether the negative tags should be added to the TNFA. */
    private boolean negtags;

    /** Whether all tags should be automatically added to the TNFA. */
    private boolean autotags = true;

    /** The disambiguation policy (true: POSIX, false: greedy). */
    boolean posix = true;

    /** The lookahead. */
    boolean lookahead;


    // -----------Configurations--------

    /* This represents configurations both for TNFAs and TDFAs. Each variant of algorithm
     * needs a different set of components:
     *
     *   TNFA posix, plain disambiguation:   q, x
     *   TNFA posix, incremental disambig.:  q, x, h, o
     *   TNFA greedy, incremental disambig.: q, x, h, o
     *   TDFA states                         q, x, v, o
     *   TDFA closure,                       q, x, v, o, y
     *
     * In order not to reimplement methods such as equals, compareto, toString, etc. one
     * single class is provided, in which the unused components are null.
     */

    /** The next Config id number. */
    private int confSeq;

    /** A configuration in FAs. */

    class Config {

        /** The identification number. */
        int id;

        /** The path segment. */
        char[] path;

        /** The origin configurations. */
        List<Config> orig;

        /** The list of loosers in comparison. */
        List<Config> loosers;

        /** The TDFA state this configuration belongs to, if any. */
        TDFAstate inState;
        /** The TNFA state. */
        TNFAstate q;

        /** The vector of registers. */
        int[] v;

        /** The vector of ordinals. */
        int[] o;

        /** The Tstring of e-path by which q is reached. */
        Tstring x;

        /** The lookahead Tstring. */
        Tstring y;

        /** The history (uses only in transduceIncremental). */
        IntVector[] h;

        /** The origin configuration state (only for Okui's case). */
        TNFAstate origin;

        /** The order (only for Okui's case). */
        int order;

        /** The accumulated tstring trie. */
        int trie;
        /**
         * Construct a configuration with the specified contents.
         *
         * @param   q TNFA state
         * @param   v vector of registers
         * @param   o vector of ordinals
         * @param   x Tstring of the e-path
         * @param   y lookahead Tstring
         * @param   h history
         * @param   p origin configuration
         */

        Config(TNFAstate q, int[] v, int[] o, Tstring x, Tstring y, IntVector[] h, Config p){
            this.id = confSeq++;
            if (p != null){
                if (!useTnfa || (useTnfa && incremental && tagless)){
                    this.orig = new LinkedList<Config>();
                    this.orig.add(p);
                }
            }
            if (!xcomp){
                if (p != null) this.path = p.path;
            }
            this.q = q;
            if (v != null) this.v = Arrays.copyOf(v,v.length);
            if (o != null) this.o = Arrays.copyOf(o,o.length);
            this.x = new Tstring(x );
            if (y != null) this.y = new Tstring(y );
            if (h != null){
                this.h = new IntVector[h.length];
                for (int i = 0; i < h.length; i++){
                    this.h[i] = new IntVector();
                    this.h[i].add(h[i]);
                }
            }
        }

        /**
         * Construct a configuration with the specified contents.
         *
         * @param   q TNFA state
         * @param   x Tstring of the e-path
         * @param   p origin configuration
         */

        Config(TNFAstate q, Tstring x, Config p){
            this(q,null,null,x,null,null,p);
        }

        /**
         * Construct a configuration with the specified contents.
         *
         * @param   q TNFA state
         * @param   h history
         * @param   o vector of ordinals
         * @param   x Tstring of the e-path
         * @param   p origin configuration
         */

        Config(TNFAstate q, IntVector[] h, int[] o, Tstring x, Config p){
            this(q,null,o,x,null,h,p);
        }

        /**
         * Construct a configuration with the specified contents.
         *
         * @param   q TNFA state
         * @param   v vector of registers
         * @param   o vector of ordinals
         * @param   x Tstring of the e-path
         * @param   p origin configuration
         */

        Config(TNFAstate q, int[] v, int[] o, Tstring x, Config p){
            this(q,v,o,x,null,null,p);
        }

        /**
         * Construct a configuration with the specified contents.
         *
         * @param   q TNFA state
         * @param   v vector of registers
         * @param   o vector of ordinals
         * @param   x Tstring of the e-path
         * @param   y lookahead Tstring
         * @param   p origin configuration
         */

        Config(TNFAstate q, int[] v, int[] o, Tstring x, Tstring y, Config p){
            this(q,v,o,x,y,null,p);
        }

        /**
         * Construct a configuration with a deep copy of the specified configuration.
         *
         * @param   c configuration
         */

        Config(Config c){
            this.id = confSeq++;
            if (c == null) return;
            if (!useTnfa || (useTnfa && incremental && tagless)){
                this.orig = new LinkedList<Config>();
                this.orig.add(c);
            }
            if (!xcomp){
                this.path = c.path;
            }
            this.q = c.q;
            if (c.v != null) this.v = Arrays.copyOf(c.v,c.v.length);
            if (c.o != null) this.o = Arrays.copyOf(c.o,c.o.length);
            this.x = new Tstring(c.x );
            if (c.y != null) this.y = new Tstring(c.y );
            if (c.h != null){
                this.h = new IntVector[c.h.length];
                for (int i = 0; i < c.h.length; i++){
                    this.h[i] = new IntVector();
                    this.h[i].add(c.h[i]);
                }
            }
            if (okui){
                this.order = c.order;
                this.origin = c.origin;
            }
            this.trie = c.trie;
        }

        /**
         * Deliver a string representing this configuration.
         *
         * @return  string
         */

        public String toString(){
            if (okui){
                return toStringk();
            }
            StringBuilder sb = new StringBuilder();
            sb.append("(");
            sb.append(this.id);
            if (this.orig != null){
                sb.append(" ->");
                sb.append(originsToString(false));
            }
            sb.append(" ");
            sb.append(this.q.number);
            if (this.v != null) sb.append(",[" + regVectorToString(this.v) + "]");
            if (this.o != null) sb.append("," + ordinalsToString(this.o));
            sb.append("," + this.x);
            if (this.y != null) sb.append(" / " + this.y);
            if (this.h != null) sb.append(",{" + historyToString(this.h) + "}");
            sb.append(")");
            return sb.toString();
        }

        /**
         * Deliver a short string representing this configuration.
         *
         * @return  string
         */

        public String toStringy(){
            StringBuilder sb = new StringBuilder();
            sb.append("(");
            sb.append(this.id);
            if (this.orig != null){
                sb.append(" ->");
                sb.append(originsToString(false));
            }
            sb.append(" ");
            sb.append(this.q.number);
            if (this.o != null) sb.append("," + ordinalsToString(this.o) + "");
            if (this.y != null) sb.append(" / " + this.y);
            sb.append(")");
            return sb.toString();
        }

        /**
         * Deliver a string representing the origins of this configuration up to the
         * ones in a TDFA state and the Tstrings in the path.
         *
         * @return  string
         */

        public String toStringp(){
            StringBuilder sb = new StringBuilder();
            sb.append("(");
            sb.append(this.id);
            if (this.orig != null){
                sb.append(" ->");
                sb.append(originsToString(true));
            }
            sb.append(" ");
            sb.append(" q:");
            sb.append(this.q.number);
            if (this.v != null) sb.append(",[" + regVectorToString(this.v) + "]");
            sb.append(", x:" + this.x);
            if (!xcomp){
                sb.append(", path:" + new Tstring(this.path ));
            }
            sb.append(")");
            return sb.toString();
        }
        /**
         * Deliver a string representing the origins of this configuration in the
         * previous TDFA states only and the Tstrings in the path.
         *
         * @return  string
         */

        public String toStringo(){
            StringBuilder sb = new StringBuilder();
            sb.append("(");
            sb.append(this.id);
            List<Config> l = getOrigins(true );
            if (l.size() > 0){
                sb.append(" ->");
                boolean first = true;
                for (Config c : l){
                    if (c.inState == null) continue;
                    if (!first) sb.append(";");
                    first = false;
                    sb.append(c.id);
                }
            }
            sb.append(" ");
            sb.append(" q:");
            sb.append(this.q.number);
            if (xcomp){
                sb.append(", path:" + this.x);
            } else {
                sb.append(", path:" + new Tstring(this.path ));
            }
            sb.append(")");
            return sb.toString();
        }
        /**
         * Deliver a string representing the origin configurations of this configuration.
         *
         * @param   <code>true</code> to stop at the configurations that belong to a TDFA
         *          state, <code>false</code> to visit all
         * @return  string
         */

        private String originsToString(boolean instate){
            StringBuilder sb = new StringBuilder();
            List<Config> lis = getOrigins(instate );
            boolean first = true;
            for (Config c : lis){
                if (!first) sb.append(";");
                first = false;
                sb.append(c.id);
                if (c.inState != null){
                    sb.append("*");
                }
            }
            return sb.toString();
        }

        /**
         * Deliver a string representing the components that are relevant for the
         * Okui's determinization.
         *
         * @return  string
         */

        public String toStringk(){
            StringBuilder sb = new StringBuilder();
            sb.append("(");
            sb.append(this.id);
            List<Config> l = getOrigins(true );
            if (l.size() > 0){
                sb.append(" ->");
                boolean first = true;
                for (Config c : l){
                    if (c.inState == null) continue;
                    if (!first) sb.append(";");
                    first = false;
                    sb.append(c.id);
                }
            }
            sb.append(" ");
            sb.append(" q:");
            sb.append(this.q.number);
            if (this.x != null && this.x.length() != 0) sb.append(",x:" + this.x);
            if (this.y != null && this.y.length() != 0) sb.append(",y:" + this.y);
            if (this.origin != null) sb.append(", origin:" + this.origin.number);
            sb.append(", order:" + this.order);
            if (xcomp){
                sb.append(", path:" + this.x);
            } else {
                sb.append(", path:" + new Tstring(this.path ));
            }
            sb.append(")");
            return sb.toString();
        }

        /**
         * Deliver the list of direct or indirect origin configurations of this configuration.
         *
         * @param   <code>true</code> to stop at the configurations that belong to a TDFA
         *          state, <code>false</code> to visit all
         * @return  list
         */

         /* An array for the configs is created, which can be rather big.
          * Another solution is to use a stack that enlarges as need occurs, and instead
          * of using an array to tell if a configuration has been visited, a test can be
          * made that the configuration is in the return lis.
          * However, this second solution is a bit slower and does not decrease the footprint.
          */

        private List<Config> getOrigins(boolean instate ){
            List<Config> lis = new LinkedList<Config>();
            if (this.orig != null){
                Config[] stack = new Config[confSeq];
                int sp = 0;
                boolean[] visited = new boolean[confSeq];
                l: for (Config c : this.orig){
                    if (visited[c.id]) continue;
                    stack[sp++] = c;
                    while (sp > 0){
                        c = stack[--sp];
                        if (visited[c.id]) continue;
                        visited[c.id] = true;
                        lis.add(c);
                        if (c.inState != null){
                            if (instate) continue;
                        }
                        if (c.orig == null) continue;
                        for (Config n : c.orig){
                            if (!visited[n.id]) stack[sp++] = n;
                        }
                    }
                }
            }
            return lis;
        }
        /**
         * Tell if this configuration is equal to the spefified other one.
         *
         * @param   other the other configuration
         * @return  <code>true</code> if equal, and <code>false</code> otherwise.
         */

        public boolean equals(Object other){
            return equals((Config)other);
        }

        /**
         * Tell if this configuration is equal to the spefified other one.
         *
         * @param   other the other configuration
         * @return  <code>true</code> if equal, and <code>false</code> otherwise.
         */

        public boolean equals(Config other){
            boolean res = false;
            doit: {
                if (other == null) break doit;
                res = other.q.number == this.q.number &&
                    (other.v == null ? this.v == null : Arrays.equals(other.v,this.v)) &&
                    (other.o == null ? this.o == null : Arrays.equals(other.o,this.o)) &&
                    (other.x == null ? this.x == null : other.x.equals(this.x)) &&
                    (other.y == null ? this.y == null : other.y.equals(this.y)) &&
                    (other.h == null ? this.h == null : arraysCompare(other.h,this.h) == 0);
            } // doit
            return res;
        }

        /**
         * Deliver the hash code.
         *
         * @return     hash code
         */

        public int hashCode(){
            return this.q.number;
        }

    }

    /**
     * Compare lexicographically the first array of IntVectors with the second one.
     *
     * @param   arr1 first array
     * @param   arr2 second array
     * @return  &lt; = or &gt; 0 if the first precedes, is equal or
     *          follows the second one
     */

    public int arraysCompare(IntVector[] arr1, IntVector[] arr2){
        if (arr1 == null && arr2 == null) return 0;
        if (arr1 == null) return -1;
        if (arr2 == null) return 1;
        int n = arr1.length;
        if (arr2.length < n) n = arr2.length;
        int i = 0;
        int j = 0;
        while (n-- != 0){
            IntVector a1 = arr1[i++];
            IntVector a2 = arr2[j++];
            int c = a1.compareTo(a2);
            if (c != 0) return c;
        }
        return arr1.length - arr2.length;
    }

    /**
     * Deliver a string representing the specified set of configurations showing only
     * the net of configurations.
     *
     * @param   confs set of configurations
     * @return  string
     */


    // ---------- TNFA -----------------

    /** An arc of the TNFA. */

    private class TNFAarc {

        /** The reference to the next transition. */
        TNFAarc next;

        /** The next state (endpoint of this arc). */
        TNFAstate nextState;

        /** The symbol. */
        Symbol sym;

        /** The number of the arc. */
        int nrEdges;
        /**
         * Deliver a string representing the label of this arc.
         *
         * @return     string
         */

        public String toLabel(){
            String str = this.sym.toString();
            if (this.sym.kind == S_TAG){
                return "t" + str;
            } else if (this.sym.kind == S_PRIO){
                return "p" + str;
            }
            return str;
        }

        /**
         * Deliver a string representing this arc.
         *
         * @return     string
         */

        public String toString(){
            return toLabel() + "->" + this.nextState.number;
        }

        /**
         * Tell if this arc is equal to the specified other one.
         *
         * @param      other the other arc
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        private boolean equals(TNFAarc other){
            if (this == other) return true;
            if (other == null) return false;
            return this.nextState == other.nextState && this.sym.equals(other.sym);
        }
    }

    /** A state of the TNFA. */

    private class TNFAstate {

        /** The reference to the next state in the list of states. */
        TNFAstate suc;

        /** The state number. */
        int number;

        /** The head of the list of arcs. */
        TNFAarc transList;

        /** Whether this state is final. */
        boolean isFinal;

        /** Whether this state is a core state (i.e. final or with nonempty arcs). */
        boolean isCore;

        /** The in-degree.*/
        int inDegree;
        /**
         * Tell if this state is equal to the specified other one.
         *
         * @param      other the other state
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        private boolean equals(TNFAstate other){
            if (this == other) return true;
            if (other == null) return false;
            return this.number == other.number;
        }
    }

    /** A state table for the TNFA. */

    private class TNFAStateTable {

        /** The head of the list of states. */
        TNFAstate head;

        /** The tail of the list. */
        TNFAstate last;

        /** The last state added. */
        TNFAstate lastAdded;

        /** The number of states. */
        int stateNr;

        /** The table of states. */
        TNFAstate[] table;

        /** The number of edges. */
        int nrEdges;

        /**
         * Add a new state.
         *
         * @param      msg string for tracing
         * @return     reference to the state
         */

        private TNFAstate add(String msg){
            TNFAstate h = new TNFAstate();
            h.number = this.stateNr++;
            if (this.last == null) this.head = h;     // append to list
            else this.last.suc = h;
            this.last = h;
            this.lastAdded = h;
            return h;
        }

        /**
         * Trace the specified state.
         *
         * @param      s state
         */

        private void traceState(TNFAstate s){
            Trc.out.printf("state: %s %s\n",s.number,
                s.isFinal ? "final" : "");
            if (s.transList != null) Trc.out.printf("  arcs:\n");
            for (TNFAarc t = s.transList; t != null; t = t.next){
                Trc.out.printf("    %s\n",t);
            }
        }

        /**
         * Trace this table of states.
         */

        private void trace(){
            for (int i = 0; i < this.stateNr; i++){
                TNFAstate s = this.table[i];
                traceState(s);
            }
            Trc.out.printf("nr tags %s\n",nrTags);
        }

        /**
         * Add an arc from the specifed state with the specified symbol or priority and
         * tag to the specified state. Arcs with priorities are kept in descending ordering.
         *
         * @param      from state
         * @param      to state
         * @param      sym symbol
         * @param      set symbol set
         * @param      prio priority
         * @param      tag tag
         * @param      msg string for tracing
         * @return     reference to the arc
         */

        private TNFAarc addArc(TNFAstate from, TNFAstate to, Symbol sym){
            return addArc(from,to,sym.sym,sym.symset,sym.prio,sym.tag,sym.cset,sym.kind,null);
        }
        private TNFAarc addArc(TNFAstate from, TNFAstate to, int sym, boolean[] symset,
            int prio, int tag, int kind){
            return addArc(from,to,sym,symset,prio,tag,null,kind,null);
        }
        private TNFAarc addArc(TNFAstate from, TNFAstate to, int sym, boolean[] symset,
            int prio, int tag, int kind, String msg){
            return addArc(from,to,sym,symset,prio,tag,null,kind,msg);
        }
        private TNFAarc addArc(TNFAstate from, TNFAstate to, int sym, boolean[] symset,
            int prio, int tag, boolean[] cset, int kind, String msg){
            TNFAarc t = null;
            sea: {
                t = new TNFAarc();
                t.nextState = to;
                t.sym = new Symbol();
                t.sym.kind = kind;
                t.sym.sym = (char)sym;
                t.sym.symset = symset;
                t.sym.prio = prio;
                t.sym.tag = tag;
                t.sym.cset = cset;
                // add it after the ones with higher priority
                if (from.transList == null){
                    from.transList = t;
                } else {
                    TNFAarc pr = null;
                    for (TNFAarc i = from.transList; i != null; i = i.next){
                        if (i.sym.kind == S_PRIO){
                            if (i.sym.prio < prio){     // add the new one before it
                                break;
                            }
                        }
                        pr = i;
                    }
                    if (pr == null){        // add at beginning
                        t.next = from.transList;
                        from.transList = t;
                    } else {
                        t.next = pr.next;
                        pr.next = t;
                    }
                }
                if (kind >= S_CHAR){            // nonempty arc
                    from.isCore = true;
                }
                if (kind < S_CHAR){
                    to.inDegree++;
                }
                this.nrEdges++;
            }
            return t;
        }

        /**
         * Trace the states reacheable from the initial one.
         */

        private void strace(){
            strace(this.head,false);
        }

        /**
         * Trace the states reacheable from the specified one.
         *
         * @param      is state
         */

        private void strace(TNFAstate is){
            strace(is,false);
        }

        /**
         * Trace the states reacheable from the specified one.
         *
         * @param      is state
         * @param      showstate <code>true</code> to trace also the state
         */

        private void strace(TNFAstate is, boolean showstate){
            int dp = 0;
            int qp = 0;
            TNFAstate[] queue = new TNFAstate[this.stateNr];
            queue[qp++] = is;                           // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                if (showstate){
                    Trc.out.printf("state %s%s\n",s.number,s.isFinal?" final":"");
                }
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    Trc.out.printf("  %s-%s\n",s.number,t);
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;          // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }
        }

        /**
         * Deliver a string representing the graph with the states reacheable from the
         * start state.
         *
         * @return     string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            int dp = 0;
            int qp = 0;
            TNFAstate[] queue = new TNFAstate[this.stateNr];
            queue[qp++] = this.head;                    // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                if (sb.length() > 0) sb.append("; ");
                sb.append(s.number);
                if (s.isFinal) sb.append("f");
                sb.append(":");
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    if (t != s.transList) sb.append(",");
                    sb.append(t);
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;  // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }
            return sb.toString();
        }

        /**
         * Remove the states that have only empty arcs redirecting their incoming arcs.
         */

        public void purge(){
            int dp = 0;
            int qp = 0;
            TNFAstate[] queue = new TNFAstate[this.stateNr];
            queue[qp++] = this.head;                    // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    TNFAstate next = t.nextState;
                    allempty: {
                        for (TNFAarc u = next.transList; u != null; u = u.next){
                            if (posix){
                                if (u.sym.kind != S_NONE
                                    && u.sym.kind != S_PRIO
                                ){
                                    break allempty;
                                }
                            } else {
                                if (u.sym.kind != S_NONE){
                                    break allempty;
                                }
                            }
                        }
                        // the next state of this arc has only empty arcs: redirect this
                        // arc to all the nextState endpoints
                        for (TNFAarc u = next.transList; u != null; u = u.next){
                            if (u == next.transList){     // first, reuse
                                t.nextState = u.nextState;
                            } else {
                                addArc(s,u.nextState,t.sym.sym,t.sym.symset,t.sym.prio,t.sym.tag,t.sym.kind);
                            }
                        }
                    }
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == next) continue loop;  // already visited
                    }
                    queue[qp++] = next;                  // enqueue it
                }
            }
        }

        /**
         * Tell if an arc with the specified data is present in the list of arcs of the
         * specified from state.
         *
         * @param      from from state
         * @param      to to state
         * @param      sym symbol
         * @return     <code>true</code> if present, <code>false</code> otherwise
         */

        private boolean searchArc(TNFAstate from, TNFAstate to, Symbol sym){
            boolean res = false;
            for (TNFAarc i = from.transList; i != null; i = i.next){
                if (i.nextState.number == to.number &&
                    i.sym.equals(sym)){
                    res = true;
                }
            }
            return res;
        }

        /**
         * Remove the espsilon arcs from the FA.
         */

        public void removeEarcs(){
            // make prio arcs empty
            if (ReTdfa.this.posix){
                for (TNFAstate p = this.head; p != null; p = p.suc){
                    for (TNFAarc t = p.transList; t != null; t = t.next){
                        if (t.sym.kind == S_PRIO) t.sym.kind = S_NONE;
                    }
                }
            }
            // transitive closure of e-paths
            boolean changed = true;
            while (changed){
                changed = false;
                for (TNFAstate p = this.head; p != null; p = p.suc){
                    for (TNFAarc t = p.transList; t != null; t = t.next){
                        if (t.sym.kind != S_NONE) continue;
                        TNFAstate q = t.nextState;
                        if (p == q) continue;
                        for (TNFAarc u = q.transList; u != null; u = u.next){
                            if (u.sym.kind != S_NONE) continue;
                            TNFAstate r = u.nextState;
                            if (r == p || r == q) continue;
                            if (!searchArc(p,r,u.sym)){
                                addArc(p,r,u.sym);
                                changed = true;
                            }
                        }
                    }
                }
            }
                        
            // backwards propagation of scanning moves over ε-arcs
            changed = true;
            while (changed){
                changed = false;
                for (TNFAstate p = this.head; p != null; p = p.suc){
                    for (TNFAarc t = p.transList; t != null; t = t.next){
                        if (t.sym.kind != S_NONE) continue;
                        TNFAstate q = t.nextState;
                        if (p == q) continue;
                        for (TNFAarc u = q.transList; u != null; u = u.next){
                            if (u.sym.kind == S_NONE) continue;
                            TNFAstate r = u.nextState;
                            if (!searchArc(p,r,u.sym)){
                                addArc(p,r,u.sym);
                                changed = true;
                            }
                        }
                    }
                }
            }

            // new final states
            // loop until no more states are made final
            changed = true;
            while (changed){
                changed = false;
                for (TNFAstate q = this.head; q != null; q = q.suc){
                    for (TNFAarc t = q.transList; t != null; t = t.next){
                        if (t.sym.kind != S_NONE) continue;
                        if (t.nextState.isFinal){
                            if (!q.isFinal){
                                changed = true;
                                q.isFinal = true;
                            }
                        }
                    }
                }
            }

            // remove all ε-arcs
            for (TNFAstate q = this.head; q != null; q = q.suc){
                TNFAarc prev = null;
                for (TNFAarc t = q.transList; t != null; t = t.next){
                    if (t.sym.kind == S_NONE){
                        if (prev == null){
                            q.transList = t.next;
                        } else {
                            prev.next = t.next;
                            prev = t;
                        }
                    } else {
                        prev = t;
                    }
                }
            }

            // remove unreacheable states
            int sp = 0;
            TNFAstate[] stack = new TNFAstate[this.stateNr];
            stack[sp++] = this.head;                    // start from it
            boolean[] visited = new boolean[this.stateNr];
            TNFAstate head = null;
            TNFAstate tail = null;
            visited[this.head.number] = true;
            while (sp > 0){                             // while start not empty
                TNFAstate s = stack[--sp];
                if (head == null){
                    head = s;
                } else {
                    tail.suc = s;
                }
                tail = s;
                s.suc = null;
                for (TNFAarc t = s.transList; t != null; t = t.next){
                    if (!visited[t.nextState.number]){
                        stack[sp++] = t.nextState;      // enqueue it
                        visited[t.nextState.number] = true;
                    }
                }
            }
            this.head = head;
        }

        /**
         * Create the specified file representing this graph in the drawgraph format.
         *
         * @paran      file name of the file
         */

        public void toGraph(String file){
            PrintStream html = null;
            try {
                html = new PrintStream(file+".js");
            } catch (FileNotFoundException exc){
                Trc.out.printf("html file error: %s\n",file);
                System.exit(1);
            }
            // emit the nodes
            int dp = 0;
            int qp = 0;
            TNFAstate[] queue = new TNFAstate[this.stateNr];
            queue[qp++] = this.head;                    // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                html.printf("var n%s = newNode(gr,\"%s\",\"%s\",\"\");\n",
                    s.number,s.number,s.isFinal?"yellow":"white");
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;  // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }

            // emit the arcs
            dp = 0;
            qp = 0;
            queue[qp++] = this.head;                    // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    String label = "";
                    if (t.sym.kind == S_TAG){
                        if (t.sym.tag > 0){
                            label += "t" + t.sym.tag;
                        } else {
                            label += "<html><span style=\'text-decoration:overline;\'>t" +
                                (-t.sym.tag) + "</span></html>";
                        }
                    } else if (t.sym.prio >= 0){
                        label += "p" + t.sym.prio;
                    } else {
                        label += t.sym.toString();
                    }
                    html.printf("newEdge(gr,\"\",\"%s\",n%s,n%s);\n",
                        label,s.number,t.nextState.number);
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;  // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }
            html.close();
        }

        /**
         * Create the nodes and arcs present in the specified string, which has the format:
         *
         *     state:[(letter|t number|p number)->state],... {;...}*
         *
         * @paran      string
         */

        void stringToGraph(String str){
            this.stateNr = 0;
            int i = 0;
            done: do {
                int c = str.indexOf(':',i);
                if (c < 0) break done;
                String s = str.substring(i,c);      // node
                boolean fin = false;
                if (s.endsWith("f")){
                    fin = true;
                    s = s.substring(0,s.length()-1);
                }
                int n = Integer.parseInt(s);
                // search state
                TNFAstate from = null;
                for (TNFAstate st = this.head; st != null; st = st.suc){
                    if (st.number == n){
                        from = st;
                        from.isFinal = fin;
                        break;
                    }
                }
                if (from == null){
                    from = add(null);
                    from.number = Integer.parseInt(s);
                    from.isFinal = fin;
                }
                i = c+1;
                for (;;){
                    if (i >= str.length()) break;
                    if (str.charAt(i) == ';') break;
                    c = str.indexOf("->",i);
                    if (c < 0) break done;
                    s = str.substring(i,c);         // arc
                    int tag = 0;
                    int prio = 0;
                    char sym = 0;
                    boolean[] symset = null;
                    int kind = S_NONE;
                    if (s.length() > 1){
                        if (s.charAt(0) == 't'){    // tag
                            s = str.substring(i+1,c);
                            tag = Integer.parseInt(s);
                            kind = S_TAG;
                        } else if (s.charAt(0) == 'p'){    // priority
                            s = str.substring(i+1,c);
                            prio = Integer.parseInt(s);
                            kind = S_PRIO;
                        } else if (s.charAt(0) == '['){    // set
                            int j = 1;
                            kind = S_SET;
                            if (s.charAt(j) == '^'){
                                kind = S_NSET;
                                j++;
                            }
                            symset = new boolean[128];
                            int prev = -1;
                            for (; j < s.length(); j++){
                                char ch = s.charAt(j);
                                if (ch == ']') break;
                                if (ch == '-'){
                                    j++;
                                    ch = s.charAt(j);
                                    for (int k = prev+1; k <= ch; k++){
                                        symset[k] = true;
                                    }
                                } else {
                                    symset[ch] = true;
                                    prev = ch;
                                }
                            }
                            if (kind == S_NSET){
                                for (int k = 0; k < symset.length; k++){
                                    symset[k] = !symset[k];
                                }
                            }
                        }
                    } else if (s.length() > 0){
                        sym = s.charAt(0);
                        kind = S_CHAR;
                        if (sym == '.'){    // dot
                            symset = new boolean[128];
                            Arrays.fill(symset,true);
                            symset['\n'] = false;
                            kind = S_DOT;
                        }
                    }
                    i = c + 2;
                    c = str.length();
                    for (int k = i; k < str.length(); k++){
                        char ch = str.charAt(k);
                        if (ch == ',' || ch == ';'){
                            c = k;
                            break;
                        }
                    }
                    s = str.substring(i,c);
                    fin = false;
                    if (s.endsWith("f")){
                        fin = true;
                        s = s.substring(0,s.length()-1);
                    }
                    n = Integer.parseInt(s);
                    // search state
                    TNFAstate to = null;
                    for (TNFAstate st = this.head; st != null; st = st.suc){
                        if (st.number == n){
                            to = st;
                            to.isFinal |= fin;
                            break;
                        }
                    }
                    if (to == null){
                        to = add(null);
                        to.number = n;
                        to.isFinal = fin;
                    }
                    addArc(from,to,sym,symset,prio,tag,kind);
                    if (c == str.length()) break;
                    if (str.charAt(c) != ',') break;
                    i = c + 1;           // skip comma
                }
                c = str.indexOf("; ",i);
                if (c < 0) break;
                i = c + 2;
            } while (true);
        }

        /**
         * Test if this fa is isomorphic with the specified one, and if it is, renumber the
         * states in the specified one so as to hav the same numbers as the corresponding
         * ones in this fa.
         *
         * @paran      other other fa
         * @return     <code>true</code> if it is isomorphic, <code>false</code> otherwise
         */

        boolean isIsomorphic(TNFAStateTable other){
            boolean res = false;
            doit: {
                if (this.stateNr != other.stateNr){
                    break doit;
                }
                TNFAstate[] map = new TNFAstate[this.stateNr];
                int dp = 0;
                int qp = 0;
                TNFAstate[] queue = new TNFAstate[this.stateNr*2];
                queue[qp++] = this.head;                    // start from it
                queue[qp++] = other.head;                   // start from it
                map[this.head.number] = other.head;
                while (dp != qp){                           // while queue not empty
                    TNFAstate s1 = queue[dp++];
                    TNFAstate s2 = queue[dp++];
                    if (map[s1.number] != s2){
                        break doit;
                    }
                    TNFAarc t1 = s1.transList;
                    TNFAarc t2 = s2.transList;
                    for (;;){
                        if ((t1 == null) != (t2 == null)){
                            break doit;
                        }
                        if (t1 == null) break;
                        if (!t1.sym.equals(t2.sym)){
                            break doit;
                        }

                        TNFAstate n1 = null;
                        for (int j = 0; j < qp; j += 2){
                            if (queue[j] == t1.nextState){    // already visited
                                n1 = t1.nextState;
                                break;
                            }
                        }
                        TNFAstate n2 = null;
                        for (int j = 1; j < qp; j += 2){
                            if (queue[j] == t2.nextState){    // already visited
                                n2 = t2.nextState;
                                break;
                            }
                        }
                        if ((n1 == null) != (n2 == null)){
                            break doit;
                        }
                        if (n1 == null){
                            queue[qp++] = t1.nextState;          // enqueue it
                            queue[qp++] = t2.nextState;          // enqueue it
                            map[t1.nextState.number] = t2.nextState;
                        } else {
                            if (map[t1.nextState.number] != t2.nextState){
                                break doit;
                            }
                        }
                        t1 = t1.next;
                        t2 = t2.next;
                    }
                }
                // make the state numbers equal
                for (TNFAstate st = this.head; st != null; st = st.suc){
                    map[st.number].number = st.number;
                }
                res = true;
            } // doit
            return res;
        }
    }

    /** The number of tags. */
    int nrTags;

    /** The number of subexpressions. */
    int nrSubExpr;

    /** The reference to the tnfa. */
    private TNFAStateTable nfa;

    /**
     * Build the TNFA using the last AST bult.
     *
     * @return     reference to the TNFA
     */

    private TNFAStateTable buildTNFA(){
        return buildTNFA(this.astRoot);
    }

    /**
     * Build the TNFA.
     *
     * @param      ast reference to the root AST
     * @return     reference to the TNFA
     */

    private TNFAStateTable buildTNFA(AstNode ast){
        this.confSeq = 0;
        this.symClassTable = null;
        TNFAStateTable nfa = new TNFAStateTable();
        this.confSeq = 1;
        nfa.nrEdges = 1;
        TNFAstate si = nfa.add("buildTNFA is");     // allocate its initial state
        TNFAstate sf = null;
        if (this.newTNFA){
            sf = nfa.add("buildTNFA fs");           // allocate its final state
            sf.isFinal = true;
            sf.isCore = true;
            nfaBuildNew(nfa,ast,si,sf);             // visit the ast recursively to build TNFA
            nfa.table = new TNFAstate[nfa.stateNr];
            for (TNFAstate s = nfa.head; s != null; s = s.suc){
                nfa.table[s.number] = s;
            }
        } else {
            sf = nfa.add("buildTNFA fs");           // allocate its final state
            sf.isFinal = true;
            sf.isCore = true;
            nfaBuild(nfa,ast,si,sf);                // visit the ast recursively to build TNFA
            // remove the empty arcs (there are)
            nfa.purge();
            nfa.table = new TNFAstate[nfa.stateNr];
            // and then remove the unreacheable states
            for (TNFAstate s = nfa.head; s != null; s = s.suc){
                s.number = -1;                         // mark all
            }
            int seq = 0;
            int dp = 0;
            int qp = 0;
            TNFAstate[] queue = new TNFAstate[nfa.stateNr];
            queue[qp++] = nfa.head;                     // start from it
            while (dp != qp){                           // while queue not empty
                TNFAstate s = queue[dp++];
                s.number = seq;
                nfa.table[seq++] = s;
                loop: for (TNFAarc t = s.transList; t != null; t = t.next){
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;    // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }
            if (seq < nfa.table.length){
                nfa.table = Arrays.copyOf(nfa.table,seq);
                nfa.stateNr = seq;
                nfa.head = null;
                TNFAstate tail = null;
                for (int i = 0; i < qp; i++){
                    TNFAstate s = queue[i];
                    s.suc = null;
                    if (nfa.head == null){
                        nfa.head = s;
                    } else {
                        tail.suc = s;
                    }
                    tail = s;
                }
            }
        }
        if (this.autotags){
            this.nrTags = this.astMap.length * 2 - 2;
        } else if (this.onetag){
            this.nrTags = 3;
        } else {
            if (this.newTNFA){
//                this.nrTags = this.tagAst.length - 1;
                if (this.autotags || this.astGroups == AST_GROUPS_ALL){
                    this.nrTags = this.astMap.length*2;
                } else {
                    this.nrTags = this.astenumi*2+1;
                }
            } else {
                // reckon the user defined tags
                this.nrTags = 0;
                for (int i = 0; i < this.astMap.length; i++){
                    AstNode a = this.astMap[i];
                    if (a.kind != A_LEA) continue;
                    if (a.sym.kind != S_TAG) continue;
                    int tag = a.sym.tag;
                    if (tag > this.nrTags) this.nrTags = tag;
                }
            }
        }

// I think that this is not needed
/*
        nfa.arcsTable = new TNFAarc[nfa.nrEdges];
        int n = 0;
        for (TNFAstate s = nfa.head; s != null; s = s.suc){
            for (TNFAarc t = s.transList; t != null; t = t.next){
                nfa.arcsTable[n] = t;
                t.nrEdges = n;
                n++;
            }
        }         
*/
        this.nfa = nfa;
        return nfa;
    }

    /* Graphs for subexpressions
     *
     * leaf
     *       o--leaf-->o
     *
     * empty
     *       o-------->o
     *
     * alternative a|b|c  (for Posix: priorities swapped)
     *
     *       o----p0--->o---a-->o---------->o
     *       `----p1--->o--p0-->o--b-->o----^
     *                  `--p1-->o--c-->o----^
     *
     * concatenation abc
     *       o--a-->o--b-->o--c-->o
     *
     * group (a)
     *       o--a-->o
     *
     * group (a)? (for Posix: priorities swapped)
     *       o-p0-->o--a-->o------>o
     *        `-----p1------------^
     *
     * group (a)* (for Posix:  priorities swapped)
     *              v--p0--,
     *       o-p0-->o--a-->o--p1-->o
     *        `----p1--------------^
     *
     * group (a)+  (for Posix: priorities swapped)
     *              v--p0--,
     *       o----->o--a-->o--p1-->o
     *
     * group (a){n}
     *       o--a-->o--...-->o--a-->o
     *
     * group (a){n,}
     *                             v--p0--,
     *       o--a-->o--...-->o---->o--a-->o--p1->o
     *
     * group (a){n,m}
     *       o--a-->o--...-->o--a-->o--p0--->o--a-->o--p0--->o--...-->o
     *                              |               |                 |
     *                              p1              p1                |
     *                              |               |                 v
     *                              `---------------+----------------->o
     *
     * N.B. the arcs are ordered with respect to P: the ones with prio 1
     * come before the ones with prio 0.
     * For POSIX, the arcs with priorities can be removed.
     */

    /**
     * Visit the specified AST recursively and build the TNFA adding arcs and states
     * to the specified initial and final states.
     *
     * @param      nfa reference to the state table
     * @param      ast reference to the AST
     * @param      is reference to the initial state
     * @param      fs reference to the final state
     */

    private TNFAarc nfaAddArc(AstNode ast, TNFAStateTable nfa, TNFAstate from,
        TNFAstate to, int sym, boolean[] symset, int prio, int tag, int kind){
        if (this.astGroups == AST_GROUPS_GRO1 && ast.implicit == 0){
            kind = S_NONE;
        }
        return nfa.addArc(from,to,sym,symset,prio,tag,kind);
    }

    /** Whether an alternative way of avoiding epsilon arcs is used. */
    private boolean newpurge = false;

    private void nfaBuild(TNFAStateTable nfa, AstNode ast, TNFAstate is, TNFAstate fs){
        // add a fake initial state, with an arc for the tag from is to it,
        // and another and an arc with the closing tag to fs

        TNFAstate ini = is;
        TNFAstate fin = fs;
        if (this.newpurge){
            ini = nfa.add("ini");                        // allocate fake init state
            fin = nfa.add("fin");                        // allocate fake end state
            nfaAddArc(ast,nfa,is,ini,0,null,0,otag(ast),S_TAG);
            nfaAddArc(ast,nfa,fin,fs,0,null,0,ctag(ast),S_TAG);
        } else {
            if (this.autotags){
                ini = nfa.add("ini");                        // allocate fake init state
                fin = nfa.add("fin");                        // allocate fake end state
                nfa.addArc(is,ini,0,null,0,otag(ast),S_TAG);
                nfa.addArc(fin,fs,0,null,0,ctag(ast),S_TAG);
            }
        }
        boolean fewNegTags = false;
        if (this.subhist){
            fewNegTags = this.okui && this.tagless && !this.finreg && this.negtags;
        } else {
            fewNegTags = this.okui && this.negtags;
        }
        if (ast.kind == A_LEA){                          // leaf
            if (ast.sym.kind >= S_CHAR){
                nfa.addArc(ini,fin,ast.sym.sym,ast.sym.symset,0,0,ast.sym.kind);
            } else {                                     // tag
                nfa.addArc(ini,fin,0,null,0,ast.sym.tag,S_TAG);
            }
        } else if (ast.kind == A_ALT){                   // alt
            // each alternative has a dfa with endpoints ci and cf
            // each that is not the first has enclosing enpoints curi and curf linked
            // to ci and cf with an arc with priority 0, and linked to the previous ones
            // with an arc with priority 1
            // the first and the last do not need these enclosing states since they can
            // connect directly
            TNFAstate previ = ini;
            TNFAstate curi = ini;
            for (AstNode i = ast.son; i != null; i = i.bro){
                TNFAstate ci = nfa.add("alt start");     // allocate initial state
                if (fewNegTags){
                    // add only the top negative tags, no nested ones
                    TNFAstate saveci = ci;
                    // if there are tags in the preceding alternatives, then put them here negated
                    for (AstNode j = ast.son; j != i; j = j.bro){
                        TNFAstate ct = nfa.add("addNegTags pre"); // allocate intermediate state
                        if (this.newpurge){
                            nfaAddArc(ast,nfa,ci,ct,0,null,0,ntag(j),S_TAG);
                        } else {
                            nfa.addArc(ci,ct,0,null,0,ntag(j),S_TAG);
                        }
                        ci = ct;
                    }
                    if (i.bro == null){                      // the last one
                        nfaBuild(nfa,i,ci,fin);
                    } else {
                        TNFAstate ct = nfa.add("addNegTags app"); // allocate intermediate state
                        nfaBuild(nfa,i,ci,fin);
                    }
                    ci = saveci;
                } else {
                    if (this.negtags){
                        TNFAstate saveci = ci;
                        TNFAstate ct = null;
                        for (AstNode a = ast.son; a != i; a = a.bro){
                            if (!areNegTags(a)) continue;
                            ct = nfa.add("addNegTags ct"); // allocate intermediate state
                            addNegTags(nfa,a,ci,ct);
                            ci = ct;
                        }
                        if (i.bro == null){
                            ct = fin;
                        } else {
                            ct = nfa.add("ct body"); // allocate intermediate state
                        }
                        nfaBuild(nfa,i,ci,ct);
                        ci = ct;
                        for (AstNode a = i.bro; a != null; a = a.bro){
                            if (!areNegTags(a)) continue;
                            if (a.bro == null){
                                ct = fin;
                            } else {
                                ct = nfa.add("addNegTags ct"); // allocate intermediate state
                            }
                            addNegTags(nfa,a,ci,ct);
                            ci = ct;
                        }
                        ci = saveci;
if (ct != fin){
    nfa.addArc(ct,fin,0,null,0,0,S_NONE,"-close");
}
                    } else {
                        nfaBuild(nfa,i,ci,fin);
                    }
/*
                } else {
// perhaps the okui one is good also for non-okui
                    if (this.negtags && areNegTagsExcl(ast,i)){
                        // N.B. there are tags to add because the call to nfaBuild introduces two
                        TNFAstate af = nfa.add("alt tags");
                        nfaBuild(nfa,i,ci,af);
                        addNegTagsExcl(nfa,ast,i,af,fin);
                    } else {
                        nfaBuild(nfa,i,ci,fin);
                    }
                }
*/
                }
                if (i.bro != null){                      // not the last one
                    if (i != ast.son){
                        curi = nfa.add("alt start1");    // allocate enclosing initial state
                    }
                    if (!this.posix){
                        nfa.addArc(curi,ci,0,null,0,0,S_PRIO);
                    } else {
                        nfa.addArc(curi,ci,0,null,1,0,S_PRIO);
                    }
                    if (i != ast.son){
                        if (!this.posix){
                            nfa.addArc(previ,curi,0,null,1,0,S_PRIO);
                        } else {
                            nfa.addArc(previ,curi,0,null,0,0,S_PRIO);
                        }
                    }
                    previ = curi;
                } else {
                    if (!this.posix){
                        nfa.addArc(previ,ci,0,null,1,0,S_PRIO);
                    } else {
                        nfa.addArc(previ,ci,0,null,0,0,S_PRIO);
                    }
                }
            }
        } else if (ast.kind == A_CON){                   // conc
            TNFAstate curs = ini;
            for (AstNode i = ast.son; i != null; i = i.bro){
                TNFAstate curf = fin;
                if (i.bro != null){
                    curf = nfa.add("conc int");          // allocate intermediate state
                }
                nfaBuild(nfa,i,curs,curf);
                curs = curf;
            }
        } else if (ast.kind == A_EMP){                   // empty
            nfa.addArc(ini,fin,0,null,0,0,S_NONE);
        } else {                                         // group
            TNFAstate ci = null;                         // group initial state
            TNFAstate cf = null;                         // group final state
            if (ast.groupKind != G_GRO && ast.groupKind != G_RE2){
                ci = nfa.add("group start");
                cf = nfa.add("group end");
            }
            switch (ast.groupKind){
            case G_GRO:
                nfaBuild(nfa,ast.son,ini,fin);           // expand its graph
                break;
            case G_OPT:                                  // optional group
                nfaBuild(nfa,ast.son,ci,cf);             // expand its graph
                if (!this.posix){
                    nfa.addArc(ini,ci,0,null,0,0,S_PRIO);
                } else {
                    nfa.addArc(ini,ci,0,null,1,0,S_PRIO);
                }
                nfa.addArc(cf,fin,0,null,0,0,S_NONE);
                if (this.negtags && areNegTags(ast.son)){
                    cf = nfa.add("opt int");             // allocate intermediate state
                    if (!this.posix){
                        nfa.addArc(ini,cf,0,null,1,0,S_PRIO);    // bypass
                    } else {
                        nfa.addArc(ini,cf,0,null,0,0,S_PRIO);    // bypass
                    }
                    if (fewNegTags){
                        if (this.newpurge){
                            nfaAddArc(ast,nfa,cf,fin,0,null,0,ntag(ast.son),S_TAG);
                        } else {
                            nfa.addArc(cf,fin,0,null,0,ntag(ast.son),S_TAG);
                        }
                    } else {
                        addNegTags(nfa,ast.son,cf,fin);
                    }
                } else {
                    if (!this.posix){
                        nfa.addArc(ini,fin,0,null,1,0,S_PRIO);   // bypass
                    } else {
                        nfa.addArc(ini,fin,0,null,0,0,S_PRIO);   // bypass
                    }
                }
                break;
            case G_RE0:                                  // kleene group
                nfaBuild(nfa,ast.son,ci,cf);             // expand its graph
                if (!this.posix){
                    nfa.addArc(ini,ci,0,null,0,0,S_PRIO);
                    nfa.addArc(cf,fin,0,null,1,0,S_PRIO);
                } else {
                    nfa.addArc(ini,ci,0,null,1,0,S_PRIO);
                    nfa.addArc(cf,fin,0,null,0,0,S_PRIO);
                }
                if (this.negtags && areNegTags(ast.son)){
                    TNFAstate tf = nfa.add("re0 int");   // allocate intermediate state
                    // no body
                    if (!this.posix){
                        nfa.addArc(ini,tf,0,null,1,0,S_PRIO);    // bypass
                    } else {
                        nfa.addArc(ini,tf,0,null,0,0,S_PRIO);    // bypass
                    }
                    if (fewNegTags){
                        if (this.newpurge){
                            nfaAddArc(ast,nfa,tf,fin,0,null,0,ntag(ast.son),S_TAG);
                        } else {
                            nfa.addArc(tf,fin,0,null,0,ntag(ast.son),S_TAG);
                        }
                    } else {
                        addNegTags(nfa,ast.son,tf,fin);
                    }
                } else {
                    if (!this.posix){
                        nfa.addArc(ini,fin,0,null,1,0,S_PRIO);      // bypass
                    } else {
                        nfa.addArc(ini,fin,0,null,0,0,S_PRIO);      // bypass
                    }
                }
                if (!this.posix){
                    nfa.addArc(cf,ci,0,null,0,0,S_PRIO);            // loopback
                } else {
                    nfa.addArc(cf,ci,0,null,1,0,S_PRIO);            // loopback
                }
                break;
            case G_RE1:                                  // +
                nfaBuild(nfa,ast.son,ci,cf);             // expand its graph
                nfa.addArc(ini,ci,0,null,0,0,S_NONE);
                if (!this.posix){
                    nfa.addArc(cf,ci,0,null,0,0,S_PRIO);     // loopback
                    nfa.addArc(cf,fin,0,null,1,0,S_PRIO);
                } else {
                    nfa.addArc(cf,ci,0,null,1,0,S_PRIO);     // loopback
                    nfa.addArc(cf,fin,0,null,0,0,S_PRIO);
                }
                break;
            case G_RE2:                                  // {n,m}
                if (ast.upperbound == 0){                // {n}
                    TNFAstate curs = ini;
                    for (int i = 0; i < ast.lowerbound; i++){
                        TNFAstate curf = fin;
                        if (i < ast.lowerbound-1){
                            curf = nfa.add("bound int"); // allocate intermediate state
                        }
                        nfaBuild(nfa,ast.son,curs,curf);
                        curs = curf;
                    }
                } else if (ast.upperbound < 0){          // {n,}
                    // n = 0 converted to *, n = 1 converted tp +
                    TNFAstate curs = ini;
                    TNFAstate curf = null;
                    for (int i = 0; i < ast.lowerbound-1; i++){
                        curf = nfa.add("bound int");     // allocate intermediate state
                        nfaBuild(nfa,ast.son,curs,curf);
                        curs = curf;
                    }
                    curs = nfa.add("bound int");         // allocate start state for last
                    nfa.addArc(curf,curs,0,null,0,0,S_NONE);
                    curf = nfa.add("bound int");         // allocate end state for last
                    nfaBuild(nfa,ast.son,curs,curf);     // expand its graph
                    nfa.addArc(curf,fin,0,null,1,0,S_PRIO);
                    nfa.addArc(curf,curs,0,null,0,0,S_PRIO);    // loopback
                } else {                                 // {n,m}
                    TNFAstate curs = ini;
                    TNFAstate curf = ini;
                    for (int i = 0; i < ast.lowerbound; i++){
                        curf = nfa.add("bound int");     // allocate intermediate state
                        nfaBuild(nfa,ast.son,curs,curf);
                        curs = curf;
                    }
                    int order = 0;
                    order = 0;
                    for (int i = ast.lowerbound; i < ast.upperbound; i++){
                        ci = nfa.add("bound opt int");
                        cf = nfa.add("bound opt end");
                        nfaBuild(nfa,ast.son,ci,cf);
                        if (order == 0){
                            if (i == 0){
                                nfa.addArc(curf,ci,0,null,0,0,S_PRIO,"arc1");
                            } else {
                                nfa.addArc(curf,ci,0,null,0,0,S_PRIO,"arc2");
                            }
                        } else if (order == 1){
                            nfa.addArc(curf,ci,0,null,0,0,S_PRIO,"arc3");
                        } else if (order == 2){
                            nfa.addArc(curf,ci,0,null,1,0,S_PRIO,"arc4");
                        } else if (order == 3){
                            if (i == 0){
                                nfa.addArc(curf,ci,0,null,0,0,S_PRIO,"arc5");
                            } else {
                                nfa.addArc(curf,ci,0,null,1,0,S_PRIO,"arc6");
                            }
                        }
                        if (this.negtags && ast.lowerbound == 0 && i == 0 && areNegTags(ast.son)){
                            TNFAstate tf = nfa.add("re0 int");   // allocate intermediate state
                            // first bypass
                            if (order == 0){
                                nfa.addArc(ini,tf,0,null,0,0,S_PRIO,"arc7");       // bypass
                            } else if (order == 1 || order == 3){
                                nfa.addArc(ini,tf,0,null,1,0,S_PRIO,"arc8");       // bypass
                            } else if (order == 2){
                                nfa.addArc(ini,tf,0,null,0,0,S_PRIO,"arc9");       // bypass
                            }
                            if (fewNegTags){
                                if (this.newpurge){
                                    nfaAddArc(ast,nfa,tf,fin,0,null,0,ntag(ast.son),S_TAG);
                                } else {
                                    nfa.addArc(tf,fin,0,null,0,ntag(ast.son),S_TAG);
                                }
                            } else {
                                addNegTags(nfa,ast.son,tf,fin);
                            }
                        } else {
                            // subsequent bypass
                            if (order == 2 || order == 3){
                                nfa.addArc(curf,fin,0,null,0,0,S_PRIO,"arc10");
                            } else {
                                nfa.addArc(curf,fin,0,null,1,0,S_PRIO,"arc11");
                            }
                        }
                        curf = cf;
                    }
                    nfa.addArc(curf,fin,0,null,0,0,S_NONE);
                }
                break;
            }
        }
    }

    private void nfaBuildNew(TNFAStateTable nfa, AstNode ast, TNFAstate is, TNFAstate fs){
        // add a fake initial state, with an arc for the tag from is to it,
        // and another and an arc with the closing tag to fs

        TNFAstate ini = is;
        TNFAstate fin = fs;
        if (this.autotags || ast.implicit != 0){
            ini = nfa.add("ini");                        // allocate fake init state
            fin = nfa.add("fin");                        // allocate fake end state
            nfa.addArc(is,ini,0,null,0,otag(ast),S_TAG,"in");
            nfa.addArc(fin,fs,0,null,0,ctag(ast),S_TAG,"out");
        }

        if (ast.kind == A_LEA){                          // leaf
            nfa.addArc(ini,fin,ast.sym.sym,ast.sym.symset,0,0,ast.sym.kind,"leaf");
        } else if (ast.kind == A_ALT){                   // alt
            for (AstNode i = ast.son; i != null; i = i.bro){
                // if there are tags in the preceding alternatives, then put them here negated
                // n.b. if there are in one alternative, then there are are on all

                TNFAstate ci = nfa.add("alt body start");  // allocate start state
                nfa.addArc(ini,ci,0,null,0,0,S_NONE,"-inempty");

                if (this.autotags || ast.son.implicit != 0){
                    TNFAstate ct = null;
                    for (AstNode a = ast.son; a != i; a = a.bro){
                        if (this.tagless && !this.finreg && this.negtags){
                            // here we enter if autotags or implicit != 0, in which case if
                            // an alternative has a tag, then all the others are forced to
                            // have also one if they do not have any
                            ct = nfa.add("addNegTags pre");    // allocate intermediate state
                            nfa.addArc(ci,ct,0,null,0,ntag(a),S_TAG,"-lead");
                            ci = ct;
                        } else {
                            if (!areNegTags(a)) continue;
                            ct = nfa.add("addNegTags ct"); // allocate intermediate state
                            addNegTags(nfa,a,ci,ct);
                            ci = ct;
                        }
                    }
                    ct = fin;
                    if (!this.tagless || this.finreg || !this.negtags){
                        if (i.bro != null){
                            ct = nfa.add("alt body end");      // allocate intermediate state
                        }
                    }
                    nfaBuildNew(nfa,i,ci,ct);
                    ci = ct;
                    if (!this.tagless || this.finreg || !this.negtags){
                        for (AstNode a = i.bro; a != null; a = a.bro){
/*
                        if (this.tagless && !this.finreg && this.negtags){
                            ct = fin;
                            if (a.bro != null){
                                ct = nfa.add("addNegTags app"); // allocate intermediate state
                            }
                            nfa.addArc(ci,ct,0,null,0,ntag(a),S_TAG,"trail");
                            ci = ct;
                        } else {
*/
                            if (!areNegTags(a)) continue;
                            if (a.bro == null){
                                ct = fin;
                            } else {
                                ct = nfa.add("addNegTags ct"); // allocate intermediate state
                            }
                            addNegTags(nfa,a,ci,ct);
                            ci = ct;
//                        }
                        }
                    }
if (ct != fin){    // no post tags
    nfa.addArc(ct,fin,0,null,0,0,S_NONE,"-close");
}
                } else {
                    nfaBuildNew(nfa,i,ci,fin);
                }
            }
        } else if (ast.kind == A_CON){                   // conc
            TNFAstate ci = ini;
            for (AstNode i = ast.son; i != null; i = i.bro){
                TNFAstate cf = fin;
                if (i.bro != null){
                    cf = nfa.add("conc int");            // allocate intermediate state
                }
                nfaBuildNew(nfa,i,ci,cf);
                ci = cf;
            }
        } else if (ast.kind == A_EMP){                   // empty
            nfa.addArc(ini,fin,0,null,0,0,S_NONE,"leaf");
        } else {                                         // group
            TNFAstate ci = null;
            TNFAstate cf = null;
            switch (ast.groupKind){
            case G_GRO:
                nfaBuildNew(nfa,ast.son,ini,fin);        // expand its graph
                break;
            case G_OPT:                                  // optional group
                ci = nfa.add("body start");              // body initial state
                nfa.addArc(ini,ci,0,null,0,0,S_NONE,"inbody");
                nfaBuildNew(nfa,ast.son,ci,fin);                               // expand its graph
                if (this.autotags || ast.son.implicit != 0){
                    if (this.tagless && !this.finreg && this.negtags){
                        nfa.addArc(ini,fin,0,null,0,ntag(ast.son),S_TAG,"bypass"); // bypass
                    } else {
                        addNegTags(nfa,ast.son,ini,fin);
                    }
                } else {
                    nfa.addArc(ini,fin,0,null,0,0,S_NONE,"bypass");
                }
                break;
            case G_RE0:                                  // kleene group
                ci = nfa.add("body start");              // body initial state
                cf = nfa.add("body end");                // body final state
                nfa.addArc(ini,ci,0,null,0,0,S_NONE,"inbody");
                nfaBuildNew(nfa,ast.son,ci,cf);          // expand its graph
                nfa.addArc(cf,fin,0,null,0,0,S_NONE,"outbody");
                nfa.addArc(cf,ci,0,null,0,0,S_NONE,"loop");     // loop
                if (this.autotags || ast.son.implicit != 0){
                    if (this.tagless && !this.finreg && this.negtags){
                        nfa.addArc(ini,fin,0,null,0,ntag(ast.son),S_TAG,"bypass");   // bypass
                    } else {
                        addNegTags(nfa,ast.son,ini,fin);
                    }
                } else {
                    nfa.addArc(ini,fin,0,null,0,0,S_NONE,"bypass");
                }
                break;
            case G_RE1:                                  // +
                cf = nfa.add("body end");                // body final state
                nfaBuildNew(nfa,ast.son,ini,cf);         // expand its graph
                nfa.addArc(cf,fin,0,null,0,0,S_NONE);
                nfa.addArc(cf,ini,0,null,0,0,S_NONE);    // loop
                break;
            case G_RE2:                                  // {n,m}
                if (ast.upperbound == 0){                // {n}
                    ci = ini;
                    for (int i = 0; i < ast.lowerbound; i++){
                        cf = fin;
                        if (i < ast.lowerbound-1){
                            cf = nfa.add("bound int");   // allocate intermediate state
                        }
                        nfaBuildNew(nfa,ast.son,ci,cf);
                        ci = cf;
                    }
                } else if (ast.upperbound < 0){          // {n,}
                    // n = 0 converted to *, n = 1 converted tp +
                    ci = ini;
                    cf = null;
                    TNFAstate prev = null;
                    for (int i = 0; i < ast.lowerbound; i++){
                        cf = nfa.add("bound int");       // allocate intermediate state
                        nfaBuildNew(nfa,ast.son,ci,cf);
                        prev = ci;
                        ci = cf;
                    }
                    nfa.addArc(cf,fin,0,null,0,0,S_NONE,"out");
                    nfa.addArc(cf,prev,0,null,0,0,S_NONE,"loop"); // loop
                } else {                                 // {n,m}
                    ci = ini;
                    cf = fin;
                    if (ast.lowerbound == 0){
                        cf = nfa.add("bound start");     // allocate intermediate state
                        nfa.addArc(ci,cf,0,null,0,0,S_NONE,"bound in");
                        if (this.negtags && areNegTags(ast.son)){
                            if (this.tagless && !this.finreg){
                                nfa.addArc(ci,fin,0,null,0,ntag(ast.son),S_TAG,"bypass");
                            } else {
                                addNegTags(nfa,ast.son,ci,fin);
                            }
                        } else {
                            nfa.addArc(ci,fin,0,null,0,0,S_NONE,"bypass");
                        }
                        ci = cf;
                    } else {
                        for (int i = 0; i < ast.lowerbound; i++){
                            cf = nfa.add("bound int");       // allocate intermediate state
                            nfaBuildNew(nfa,ast.son,ci,cf);
                            ci = cf;
                        }
                    }
                    for (int i = ast.lowerbound; i < ast.upperbound; i++){
                        if (ast.lowerbound > 0 || i > ast.lowerbound){
                            nfa.addArc(cf,fin,0,null,0,0,S_NONE,"bypass");
                            ci = cf;
                            cf = nfa.add("bound opt epsilon");
                            nfa.addArc(ci,cf,0,null,0,0,S_NONE,"nrct in");
                        }
                        ci = cf;
                        cf = fin;
                        if (i < ast.upperbound-1){
                            cf = nfa.add("bound opt int");
                        }
                        nfaBuildNew(nfa,ast.son,ci,cf);
                    }
                }
                break;
            }
        }
    }


    /**
     * Test whether there are tags present in the asts rooted in the specified one excluding
     * the specified node.
     *
     * @param      nfa reference to the state table
     * @param      ast reference to the root AST
     * @param      excl reference to the AST to exclude
     * @return     <code>true</code> if there are, <code>false</code> otherwise
     */

    private boolean areNegTagsExcl(AstNode ast, AstNode excl){
        if (this.autotags || ast.implicit != 0) return true;
        boolean res = false;
        for (AstNode i = ast.son; i != null; i = i.bro){
            if (i == excl) continue;
            res = areNegTags(i);
            if (res) break;
        }
        return res;
    }

    /**
     * Test whether there are tags present in the asts rooted in the specified one.
     *
     * @param      nfa reference to the state table
     * @param      ast reference to the root AST
     * @return     <code>true</code> if there are, <code>false</code> otherwise
     */

    private boolean areNegTags(AstNode ast){
        if (this.autotags || ast.implicit != 0) return true;
        int sp = 0;
        AstNode[] stack = new AstNode[this.astMap.length];
        stack[sp++] = ast;                        // push it
        // count the nodes
        int nrNodes = 0;
        while (sp > 0){                           // while stack not empty
            AstNode n = stack[--sp];              // pop
            if (n.kind == A_LEA && n.sym.kind == S_TAG && n.sym.tag > 0) nrNodes++;
            for (AstNode a = n.son; a != null; a = a.bro){
                if (sp >= stack.length){
                    stack = Arrays.copyOf(stack,stack.length+10);
                }
                stack[sp++] = a;                  // push it
            }
        }
        return nrNodes > 0;
    }

    /**
     * Add the negative tags corresponding to the ones present in the asts rooted in the
     * specified one excluding the specified node generating a sequence of states and arcs
     * to the specified initial and final states.
     *
     * @param      nfa reference to the state table
     * @param      ast reference to the root AST
     * @param      excl reference to the AST to exclude
     * @param      is reference to the initial state
     * @param      fs reference to the final state
     */

    private void addNegTagsExcl(TNFAStateTable nfa, AstNode ast, AstNode excl,
        TNFAstate is, TNFAstate fs){
        TNFAstate ci = is;
        for (AstNode i = ast.son; i != null; i = i.bro){
            if (i == excl) continue;
            TNFAstate cf = fs;
            if (i.bro != null && (i.bro != excl || i.bro == excl && i.bro.bro != null)){
                cf = nfa.add("addNegTags cf"); // allocate intermediate state
            }
            addNegTags(nfa,i,ci,cf);
            ci = cf;
        }
    }

    /**
     * Add the negative tags corresponding to the ones present in the specified ast
     * generating a sequence of states and arcs to the specified initial and final states.
     *
     * @param      nfa reference to the state table
     * @param      ast reference to the root AST
     * @param      is reference to the initial state
     * @param      fs reference to the final state
     */

    private void addNegTags(TNFAStateTable nfa, AstNode ast, TNFAstate is, TNFAstate fs){
        if (this.subhist){
            IntVector ntags = new IntVector();
            addNegTags(nfa,ast,ntags);
            for (int i = 0; i < ntags.size(); i++){
                int tag = ntags.get(i);
                TNFAstate ct = fs;
                if (i < ntags.size()-1){                 // intermediate one
                    ct = nfa.add("addNegTags ct");       // allocate intermediate state
                }
                TNFAarc arc = null;
                if (this.newpurge){
                    arc = nfaAddArc(ast,nfa,is,ct,0,null,0,tag,S_TAG);
                } else {
                    arc = nfa.addArc(is,ct,0,null,0,tag,S_TAG);
                }
                is = ct;
            }
            return;
        }

        int sp = 0;
        AstNode[] stack = new AstNode[this.astMap.length];
        stack[sp++] = ast;                        // push it
        // count the nodes
        int nrNodes = 0;
        while (sp > 0){                           // while stack not empty
            AstNode n = stack[--sp];              // pop
            if (this.autotags || n.implicit != 0){
                nrNodes++;
            } else {
                if (n.kind == A_LEA && n.sym.kind == S_TAG && n.sym.tag > 0) nrNodes++;
            }
            for (AstNode a = n.son; a != null; a = a.bro){
                if (sp >= stack.length){
                    stack = Arrays.copyOf(stack,stack.length+10);
                }
                stack[sp++] = a;                  // push it
            }
        }
        // then generate the nodes and arcs
        sp = 0;
        stack[sp++] = ast;                        // push it
        while (sp > 0){                           // while stack not empty
            AstNode n = stack[--sp];              // pop
            if (this.autotags || n.implicit != 0){
                TNFAstate ct = nfa.add("addNegTags ct"); // allocate intermediate state
                TNFAarc arc = null;
                if (this.newpurge){
                    arc = nfaAddArc(ast,nfa,is,ct,0,null,0,ntag(n),S_TAG);
                } else {
                    arc = nfa.addArc(is,ct,0,null,0,ntag(n),S_TAG);
                }
                is = ct;
                TNFAstate curf = fs;
                if (--nrNodes > 0){
                    curf = nfa.add("addNegTags int"); // allocate intermediate state
                }
                // here we have the closing negative tags
                if (this.newpurge){
                    arc = nfaAddArc(ast,nfa,is,curf,0,null,0,cntag(n),S_TAG);
                } else {
                    arc = nfa.addArc(is,curf,0,null,0,cntag(n),S_TAG);
                }
                is = curf;
            } else {
                if (n.kind == A_LEA && n.sym.kind >= S_TAG && n.sym.tag > 0){
                    TNFAstate curf = fs;
                    if (--nrNodes > 0){
                        curf = nfa.add("addNegTags int"); // allocate intermediate state
                    }
                    TNFAarc arc = null;
                    if (this.newpurge){
                        arc = nfaAddArc(ast,nfa,is,curf,0,null,0,-n.sym.tag,S_TAG);
                    } else {
                        arc = nfa.addArc(is,curf,0,null,0,-n.sym.tag,S_TAG);
                    }
                    is = curf;
                }
            }

            for (AstNode a = n.son; a != null; a = a.bro){
                sp++;                             // reserve space
            }
            int p = sp;
            for (AstNode a = n.son; a != null; a = a.bro){
                stack[--p] = a;                   // push it
            }
        }
    }

    private void addNegTags(TNFAStateTable nfa, AstNode ast, IntVector ntags){
        if (this.autotags || ast.implicit != 0){
            ntags.add(ntag(ast));
            for (AstNode a = ast.son; a != null; a = a.bro){
                addNegTags(nfa,a,ntags);
            }
            ntags.add(cntag(ast));
        }
    }


    /**
     * Run the TNFA with the specified string and deliver the LST of the prior tree.
     *
     * @param      str string
     * @return     <code>true</code> if successful, <code>false</code> otherwise
     */

    private boolean transduce(String str){
        boolean res = transduce(this.nfa,str);
        return res;
    }

    /**
     * Run the specified TNFA with the specified string and deliver the LST of the prior tree.
     *
     * @param      nfa reference to the state table
     * @param      str string
     * @return     <code>true</code> if successful, <code>false</code> otherwise
     */

    private boolean transduce(TNFAStateTable nfa, String str){
        this.error = false;
        this.confSeq = 1;
        if (nfa.head == null) return true;         // phi
        if (this.posix){
            if (this.incremental){
                return transduceIncremental(nfa,str);
            } else {
                return transducePlain(nfa,str,true);
            }
        } else {
            if (this.incremental){
                return transduceIncremental(nfa,str);
            } else {
                return transducePlain(nfa,str,false);
            }
        }
    }

    /**
     * Run the TNFA with the specified string and deliver the LST of the prior POSIX or greedy tree.
     *
     * @param      nfa reference to the state table
     * @param      str string
     * @param      posix <code>true</code> if POSIX, <code>false</code> GREEDY
     * @return     <code>true</code> if successful, <code>false</code> otherwise
     */

    /* This produces a DAG of configurations that is headed by the reached and configs
     * lists. After making a closure, the reached list is no longer needed (but the configurations
     * referred to by it are needed). After making a closure, some parts of the DAG could become
     * useless, and are thus freed.
     * Actually, since transducePlain collects the final tstring in the .x components of
     * configurations, it does not need to keep refereces from configurations to their orinig
     * ones (i.e. the DAG). However, to make the method simple we keep it and remove the
     * dangling parts of the DAG. Note that the method has not much practical use since the
     * TNFA efficient one is transduceIncremental.
     */

private TstringTrie tstrie;
    private boolean transducePlain(TNFAStateTable nfa, String str, boolean posix){
if (this.tagless){
    if (this.tstrie == null){
        this.tstrie = new TstringTrie();
    } else {
        this.tstrie.init();
    }
}
        List<Config> configs = new LinkedList<Config>();
        List<Config> init = new LinkedList<Config>();
        List<Config> reached = new LinkedList<Config>();
        Config ci = new Config(nfa.head,null,null);
        init.add(ci);
        TDFAstate fake = new TDFAstate();         // fake state to trace origin closures
        XclosureResult res = null;
        if (this.okui){
            res = new XclosureResult();
        }
        configs = closureConf(nfa,init,configs,null,res);
        if (posix && this.okui){
            fake.bmatrix = res.bmatrix;
        }
        for (Config j : configs){
            if (this.tagless){
                j.trie = this.tstrie.append(0,j.y);
            } else {
                j.x = j.y;
            }
            j.y = null;
            j.inState = fake;
        }
        init.clear();

        for (int i = 0; i < str.length(); i++){
            if (str.charAt(i) >= 128){
                this.error = true;
                return false;
            }
            reach(nfa,configs,str.charAt(i),reached);

for (Config j : reached){
    if (this.tagless){
        j.trie = this.tstrie.append(j.trie,j.x);
        j.y = null;
        j.x = null;
    }
}

            configs.clear();
            configs = closureConf(nfa,reached,configs,fake,res);
            if (posix && this.okui){
                fake.bmatrix = res.bmatrix;
            }
            for (Config j : configs){
                if (this.tagless){
                    j.trie = this.tstrie.append(j.trie,j.y);
                    j.x = null;
                    j.y = null;
                } else {
                    j.x.append(j.y);
                }
                j.y = null;
                j.inState = fake;
            }
        }
        Config fin = null;
        boolean matched = false;
        for (Config i : configs){
            if (!i.q.isFinal) continue;
            matched = true;
            if (this.tagless){
                this.treeLen = this.tstrie.length(i.trie);
            } else {
                this.treeLen = i.x.length();
            }
            fin = i;
        }
        if (!matched){
            this.error = true;
        } else {
            if (this.finreg || this.matchTstring){
                if (this.treearr == null || this.treearr.length < this.treeLen){
                    this.treearr = new char[this.treeLen];
                }
                if (this.tagless){
                    this.tstrie.copy(fin.trie,this.treearr,this.treeLen);
                } else {
                    fin.x.copy(this.treearr,0);
                }
                if (this.finreg){
                    computeHistoriesTstring();
                    if (!this.matchTstring) this.treeLen = 0;
                }
                if (this.parsetree){
                    buildTreeTrie(fin.trie,this.text);
                }
            } else {
                this.treeLen = 0;
            }
        }
        return !this.error;
    }

    private void traceConfigsDag(List<Config> configs){
        Config[] stack = new Config[this.confSeq];
        int sp = 0;
        boolean[] visited = new boolean[this.confSeq];
        for (Config i : configs){
            visited[i.id] = true;
            Trc.out.printf("%s:",i.id);
            if (i.orig != null){
                for (Config c : i.orig){
                    Trc.out.printf(" %s",c.id);
                }
            }
            Trc.out.printf("\n");
            if (i.orig == null) continue;
            for (Config c : i.orig){
                if (visited[c.id]) continue;
                stack[sp++] = c;
                while (sp > 0){
                    c = stack[--sp];
                    if (visited[c.id]) continue;
                    visited[c.id] = true;
                    Trc.out.printf("%s:",c.id);
                    if (c.orig != null){
                        for (Config n : c.orig){
                            Trc.out.printf(" %s",n.id);
                        }
                    }
                    Trc.out.printf("\n");
                    if (c.orig == null) continue;
                    for (Config n : c.orig){
                        if (!visited[n.id]) stack[sp++] = n;
                    }
                }
            }
        }
    }


    /**
     * Deliver the configurations representing the states that are reached form the ones
     * of the specified starting configurations with arcs labelled with the specified character
     * or character class.
     *
     * @param      nfa reference to the state table
     * @param      configs starting configurations
     * @param      c character or character class
     * @param      reached set to be filled with the reached configurations
     */

    private void reach(TNFAStateTable nfa, List<Config> configs, char c,
        List<Config> reached){
        reached.clear();
        for (Config i : configs){
            for (TNFAarc t = i.q.transList; t != null; t = t.next){
                if (t.sym.kind >= S_CHAR){ 
                    boolean cclass = false;
                    found: if (t.sym.kind == S_CSET){
                        if (t.sym.cset != null && t.sym.cset[c]){
                            cclass = true;
                            break found;
                        }
                        continue;
                    } else {
                        if (t.sym.symset != null && t.sym.symset[c] ||
                            t.sym.sym == c) break found;
                        continue;
                    }
                    Tstring ts = new Tstring();
                    ts.append(i.x);
                    if (cclass){
                        ts.appendClass(c);
                    } else {
                        ts.append(c);
                    }
                    Config conf = new Config(i);
                    conf.q = t.nextState;
                    conf.x = ts;
                    if (this.okui){
                        conf.origin = i.q;
                    }
                    reached.add(conf);
                    break;
                }
            }
        }
    }

    /** A representation of the infinite offset. */
    private final static int INFINITE = Integer.MAX_VALUE;

    /**
     * Compare the specified Tstrings and tell if the first precedes the second one in the
     * POSIX ordering.
     *
     * @param      x first Tstring
     * @param      y second Tstring
     * @result     <code>true</code> if the first precedes the second, and <code>false</code> otherwise.
     */

    private boolean ordPosix(Tstring x, Tstring y){
        if (x.equals(y)){
            return true;
        }
        boolean res = false;
        String reason = "";
        String reasonA = "";
        String reasonB = "";
        String reasonC = "";
        String reasonD = "";
        int subexp = 0;
        int subh = 0;
        loop: for (int t = 1; t <= this.nrSubExpr; t++){     // number of subexpressions
            subexp = t;
            IntVector[] A = history(x,2*t-1);
            IntVector[] C = history(x,2*t);
            IntVector[] B = history(y,2*t-1);
            IntVector[] D = history(y,2*t);
            if (A.length != B.length || A.length != C.length || A.length != D.length){
                Trc.out.printf("ordPosix \"%s\" <=> \"%s\"\n",x,y);
                Trc.out.printf("ordPosix diff lengths: A: %s C: %s B: %s D: %s tags: %s,%s\n",
                    A.length,C.length,B.length,D.length,2*t-1,2*t);
                Trc.out.printf("histories A: %s C: %s B: %s D: %s\n",historyToString(A),
                    historyToString(C),historyToString(B),historyToString(D));
            }
            int len = Math.min(A.length,B.length);
            for (int i = 0; i < len; i++){
                subh = i;
                IntVector Ai = A[i];
                IntVector Ci = C[i];
                if (Ci.size() < Ai.size()){
                    if (Ci.size() != Ai.size()-1){
                        Trc.out.printf("ordPosix diff Ai, Ci lengths: %s %s\n",Ai,Ci);
                    }
                    Ci.add(INFINITE);
                }
                IntVector Bi = B[i];
                IntVector Di = D[i];
                if (Di.size() < Bi.size()){
                    if (Di.size() != Bi.size()-1){
                        Trc.out.printf("ordPosix diff Bi, Di lengths: %s %s\n",Bi,Di);
                    }
                    Di.add(INFINITE);
                }
                int m = Ai.size();
                int k = Bi.size();
                reasonA = "";
                reasonB = "";
                reasonC = "";
                reasonD = "";
                for (int j = 0; j < Math.min(m,k); j++){
                    int aj = Ai.get(j);
                    int bj = Bi.get(j);
                    int cj = Ci.get(j);
                    int dj = Di.get(j);
                    reasonA += (j > 0 ? " " : "") + (aj == INFINITE ? "\u221e" : aj);
                    reasonB += (j > 0 ? " " : "") + (bj == INFINITE ? "\u221e" : bj);
                    reasonC += (j > 0 ? " " : "") + (cj == INFINITE ? "\u221e" : cj);
                    reasonD += (j > 0 ? " " : "") + (dj == INFINITE ? "\u221e" : dj);
                    if (aj != bj){
                        reasonA += "*";
                        reasonB += "*";
                        if (aj == -1) break loop;
                        if (bj == -1){
                            res = true;
                            break loop;
                        }
                        res = aj < bj;
                        break loop;
                    }
                    if (cj != dj){
                        reasonC += "*";
                        reasonD += "*";
                        res = cj > dj;
                        break loop;
                    }
                }
                if (m != k){
                    reasonA += "len: " + Ai.size();
                    reasonB += "len: " + Bi.size();
                    res = m < k;
                    break loop;
                }
            }
            if (A.length != B.length){
                reasonA = "len: " + A.length;
                reasonB = "len: " + B.length;
                break loop;
            }
        }
        /*
        boolean res1 = ordPosixSimpl(x,y);
        if (res1 != res){
            reason = "subexp " + subexp + "(t" + (2*subexp-1) + ",t" + (2*subexp) +
                "): A<sub>" + subh + "</sub> " + reasonA + " <=> B<sub>" + subh + "</sub> " + reasonB + " | "+
                "C<sub>" + subh + "</sub> " + reasonC + " <=> D<sub>" + subh + "</sub> " + reasonD;
            Trc.out.printf("ordPosix \"%s\" %s \"%s\" diff simpl %s\n",x,res?"<":">",y,res1?"<":">");
            Trc.out.printf("ordPosix why %s simpl %s\n",reason,reasonSimpl);
        }
        */
        return res;
    }

    /**
     * Compare in an optimized way the specified Tstrings and tell if the first precedes the
     * second one in the POSIX ordering.
     *
     * @param      x first Tstring
     * @param      y second Tstring
     * @result     <code>true</code> if the first precedes the second, and <code>false</code> otherwise.
     */

    private boolean ordPosixSimpl(Tstring x, Tstring y){
        if (x.equals(y)){
            return true;
        }
        boolean res = false;
        String reason = "";
        String reasonA = "";
        String reasonB = "";
        int subexp = 0;
        int subh = 0;
        loop: for (int t = 1; t <= this.nrSubExpr; t++){     // number of subexpressions
            subexp = t;
            IntVector[] A = history(x,2*t);
            IntVector[] B = history(y,2*t);
            int len = Math.min(A.length,B.length);
            for (int i = 0; i < len; i++){
                subh = i;
                IntVector Ai = A[i];
                IntVector Bi = B[i];
                reasonA = "";
                reasonB = "";
                if (!Ai.equals(Bi)){
                    // res = subhistory(Ai,Bi) < 0;
                    for (int j = 0; j < Math.min(Ai.size(),Bi.size()); j++){
                        int aj = Ai.get(j);
                        int bj = Bi.get(j);
                        reasonA += (j > 0 ? " " : "") + (aj == INFINITE ? "\u221e" : aj);
                        reasonB += (j > 0 ? " " : "") + (bj == INFINITE ? "\u221e" : bj);
                        if (aj != bj){
                            reasonA += "*";
                            reasonB += "*";
                            res = aj > bj;
                            break loop;
                        }
                    }
                    reasonA += "len: " + Ai.size();
                    reasonB += "len: " + Bi.size();
                    res = Ai.size() < Bi.size();
                    break loop;
                }
            }
        }
        // use the same letters as ordPosix to denote the end tags
        reasonSimpl = "subexp " + subexp + "(t" + (2*subexp-1) + ",t" + (2*subexp) +
            "): C<sub>" + subh + "</sub> " + reasonA + " <=> D<sub>" + subh + "</sub> " + reasonB;
        return res;
    }

    /** A string representing the reason of the last comparison. */
    private String reasonSimpl;

    /**
     * Deliver the history of the specifed tag in the specified Tstring.
     * second one in the POSIX ordering.
     *
     * @param      a Tstring
     * @param      t tag
     * @result     history
     */

    private IntVector[] history(Tstring a, int t){
        int i = 0;
        int pos = 0;
        IntVector[] arr = new IntVector[1];
        arr[0] = new IntVector();
        int j = 0;
        for (;;){
            for (; i < a.string.length(); i++){
                int tag = a.getTag(i);
                if (tag == t || tag == -t) break;
                if (tag == 0) pos++;
            }
            l: for (; i < a.string.length(); i++){
                int tag = a.getTag(i);
                if (tag == 0){
                    pos++;
                } else {
                    for (int u = 0; u < 2*Math.ceil(t/2.0)-1; u++){
                        if (tag == u || tag == -u){
                            break l;
                        }
                    }
                    if (tag == t){
                        arr[j].add(pos);
                    }
                    if (tag == -t){
                        arr[j].add(-1);       // -1 = phi
                    }
                    if (tag == t || tag == -t){
                    }
                }
            }
            if (i >= a.string.length()) break;
            j++;
            if (j >= arr.length){
                arr = Arrays.copyOf(arr,j+1);
            }
            if (arr[j] == null) arr[j] = new IntVector();
        }
        return arr;
    }

    /**
     * Deliver a string representing the specified history.
     *
     * @param      arr history
     * @result     string
     */

    private static String historyToString(IntVector[] arr){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.length; i++){
            if (i > 0) sb.append(",");
            sb.append(subHistoryToString(arr[i]));
        }
        return sb.toString();
    }

    /**
     * Deliver a string representing the specified subhistory.
     *
     * @param      arr subhistory
     * @result     string
     */

    private static String subHistoryToString(IntVector arr){
        StringBuilder sb = new StringBuilder();
        if (arr == null){
            sb.append("[null]");
        } else {
            sb.append("[");
            for (int j = 0; j < arr.size(); j++){
                if (j > 0) sb.append(", ");
                int v = arr.get(j);
                if (v == INFINITE){
                    sb.append("\u221e");
                } else {
                    sb.append(v);
                }
            }
            sb.append("]");
        }
        return sb.toString();
    }

    /**
     * Run the TNFA with the specified string and deliver the LST of the prior
     * tree using incremental disambiguation.
     *
     * @param      nfa reference to the state table
     * @param      str string
     * @return     <code>true</code> if successful, <code>false</code> otherwise
     */

    private boolean transduceIncremental(TNFAStateTable nfa, String str){
        List<Config> configs = new LinkedList<Config>();
        List<Config> init = new LinkedList<Config>();
        List<Config> reached = new LinkedList<Config>();
        int N = this.nrTags;
        int[] initord = null;
        IntVector[] inith = null;
        if (!this.okui || !this.tagless){
            inith = new IntVector[N+1];
            initord = new int[N+1];
            for (int t = 1; t <= N; t++){             // number of tags
                initord[t] = 0;
                inith[t] = new IntVector();
            }
        }
        Config ci = new Config(nfa.head,inith,initord,null,null);
        init.add(ci);
        TDFAstate fake = new TDFAstate();         // fake state to trace origin closures

        XclosureResult res = null;
        if (this.okui){
            res = new XclosureResult();
        }
        configs = closureConf(nfa,init,configs,null,res);
        if (this.okui){
            fake.bmatrix = res.bmatrix;
        }
        for (Config j : configs){
            j.x = j.y;
            j.y = null;
            if (this.okui && this.tagless) continue;
            if (j.x == null){
                j.x = new Tstring();
            }
            for (int l = 0; l < j.x.length(); l++){
                int t = j.x.getTag(l);
                if (this.subhist){
                    addHistSep(t,l,j.x,j.h);
                }
                if (t > 0){
                    j.h[t].add(0);
                } else if (t < 0){
                    j.h[-t].add(-1);
                }
            }
        }
        for (Config j : configs){
            j.inState = fake;
        }
        for (int i = 0; i < str.length(); i++){
            if (str.charAt(i) >= 128){
                this.error = true;
                return false;
            }

            reach(nfa,configs,str.charAt(i),reached);
            if (reached.size() == 0){
                this.error = true;
                return false;
            }
            if (this.posix){
                for (Config j : reached){
                    j.y = null;
                    j.x = null;
                }
            } else {
                for (Config j : reached){
                    j.x = null;
                }
            }
            configs.clear();
            configs = closureConf(nfa,reached,configs,fake,res);
            if (this.okui){
                fake.bmatrix = res.bmatrix;
            }
            for (Config j : configs){
                j.x = j.y;
                j.y = null;
            }
            for (Config j : configs){
                // update_histories(j.h,j.x,i);
                if (j.x == null) j.x = new Tstring();
                Tstring s = j.x;
                if (this.okui && this.tagless) continue;
                for (int l = 0; l < s.length(); l++){
                    int t = s.getTag(l);
                    if (this.subhist){
                        addHistSep(t,l,j.x,j.h);
                    }
                    if (t > 0){
                        j.h[t].add(i+1);
                    } else if (t < 0){
                        j.h[-t].add(-1);
                    }
                }
            }
            for (Config j : configs){
                j.inState = fake;
            }
        }
        int[][] finalHist;
        boolean first = true;
        for (Config i : configs){
            if (!i.q.isFinal) continue;
            if (first){
                // there is only one because it is final, and two finals would be disambiguated
                first = false;
                if (!this.tagless){
                    if (this.finreg || this.matchTstring){
                        finalHist = new int[i.h.length][];
                        this.finalRegisters = finalHist;
                        for (int j = 1; j < finalHist.length; j++){
                            finalHist[j] = i.h[j].toArray();
                        }
                        if (this.matchTstring){
                            tagsToTstring(finalHist,str,false);
                        }
                    }
                } else {
                    if (this.matchTstring || this.finreg){
                        confchainToTree(i,str);
                        if (this.finreg){
                            computeHistoriesTstring();
                            if (!this.matchTstring) this.treeLen = 0;
                        }
                    }
                }
                if (this.parsetree){
                    buildTree(i,str);
                }
            } else {
                this.error = true;
                break;
            }
        }
        if (first){
            this.error = true;
        }
        if (this.matchTstring){
        }
        return !this.error;
    }

    /**
     * Add a separator to the subhistories of the specified tag if the tag at the current
     * index in the specified Tstring is preceded by its encloding tag and the subhistory
     * is not the first one for the specified tag.
     *
     * @param      t tag
     * @param      l index in the Tstring
     * @param      x Tstring
     * @param      h accumulated Tstrings
     */

    private void addHistSep(int t, int l, Tstring x, IntVector[] h){
        if (t < 0) t = -t;
        AstNode ast = this.astMap[this.tagAst[t]];
        if (ast.fat == null || ast.fat.kind != A_GRO) return;
        if (t % 2 == 1 && l > 0){           // opening tag
            int r = x.getTag(l-1);
            if (r < 0) r = -r;
            AstNode enc = ast.fat;
            if (enc != null && r == otag(enc)){
                if (h[t].size() > 0){
                    h[t].add(-2);
                }
            }
        }
    }

    /**
     * Compute the Tstring from the chain of configurations.
     *
     * @param      fc head of the chain
     * @param      text matched string
     */

    /* The chain of configurations is such that a configuration in a state is linked to only
     * one other in the previous state thru the origin links. When a configuration is built,
     * (representing the visiting of an arc), its origin link points to the configuration
     * that represents the previous segment in the path that continues with the arc being
     * visited. At the end of a closure, or a reach() we have then a set of configurations
     * linked to previous, originating configurations. There cannot be two configurations
     * ending in a same state because one of the two would have been removed by disambiguation.
     * N.B. Actually, a configuration points to the previous one, which can be one created
     * by reach() or closure(), which can eventually point to one belonging to the previous
     * state (i.e. resulting from the previous closure). This means that there is a need to
     * follow these links to find the previous one in the chain.
     * In the optimized closure the created resulting configurations point to the ones delivered
     * by reach(), which in turn point to the one of the previous closure, so to get to the
     * configurations of the last state only two hops are needed.
     */

    private void confchainToTree(Config fc, String text){
        // measure the LST
        int i = text.length();
        Config[] confseq = new Config[i+1];
        int len = 0;
        for (Config c = fc; c != null;){
            confseq[i] = c;
            if (this.xcomp){
                len += c.x.length();
            } else {
                if (this.finreg){
                    len += c.x.length();
                } else {
                    len += c.path.length;
                }
            }
            if (i == 0) break;
            --i;
            c = c.orig.get(0);
            if (c != null){
                c = c.orig.get(0);
            }
            len++;
        }
        // allocate it
        if (this.treearr == null || this.treearr.length < len){
            this.treearr = new char[len];
        }
        this.treeLen = len;
        // then fill it
        i = 0;
        int textlen = text.length();
        len = textlen + 1;
        for (int j = 0; j < len; j++){
            Config c = confseq[j];
            if (this.xcomp){
                c.x.copy(this.treearr,i);
                i += c.x.length();
            } else {
                if (this.finreg){
                    c.x.copy(this.treearr,i);
                    i += c.x.length();
                } else {
                    System.arraycopy(c.path,0,this.treearr,i,c.path.length);
                    i += c.path.length;
                }
            }
            if (j < textlen){
                this.treearr[i++] = text.charAt(j);
                if (this.xcomp){
                } else {
                    if (this.finreg){
                    } else {
                    }
                }
            }
        }
/*
        if (!this.xcomp){
            TRACE(M,"fc: %s\n",fc.id);
            if (this.finreg){
                fc.x.copy(this.treearr,i);
            } else {
                System.arraycopy(fc.path,0,this.treearr,i,fc.path.length);
            }
        }
*/
    }

    /**
     * Deliver the configurations describing the paths to the states reached from the specified
     * ones with arcs labelled with tags or prios. Thread cycles only once.
     * Discard paths whose Tstrings are not prior for the leftmost-greedy policy.
     *
     * @param      nfa reference to the state table
     * @param      reached start states
     * @param      configs reached states
     */

    private void closure_leftmost(TNFAStateTable nfa, List<Config> reached,
        List<Config> configs){
        int sp = 0;
        Config[] stack = new Config[reached.size()];
        Config[] result = new Config[nfa.stateNr];
        configs.clear();
        // push them in reverse ordering
        int nconf = reached.size();
        sp = nconf;
        for (Config i : reached){
            stack[--sp] = i;
        }
        sp = nconf;
        while (sp > 0){                              // while stack not empty
            Config c = stack[--sp];
            if (result[c.q.number] != null) continue;
            result[c.q.number] = c;
            if (c.q.isCore){
                Config conf = new Config(c);
                configs.add(conf);
                if (!this.xcomp){
                    int len = 0;
                    for (int j = 0; j < conf.y.length(); j++){
                        int t = conf.y.getTag(j);
                        if (!this.tagless && !this.useTnfa){
                            if (this.finreg){
                                if (t >= 0 && this.fixedTags){
                                    if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                                }
                            } else {
                                if (t <= 0) continue;
                            }
                        } else {
                            if (t <= 0) continue;
                        }
                        len++;
                    }
                    conf.path = new char[len];
                    len = 0;
                    for (int j = 0; j < conf.y.length(); j++){
                        int t = conf.y.getTag(j);
                        if (!this.tagless && !this.useTnfa){
                            if (this.finreg){
                                if (t >= 0 && this.fixedTags){
                                    if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                                }
                            } else {
                                if (t <= 0) continue;
                            }
                        } else {
                            if (t <= 0) continue;
                        }
                        conf.path[len++] = conf.y.charAt(j);
                    }
                }
            }
            for (TNFAarc t = c.q.transList; t != null; t = t.next){
                if (t.sym.kind == S_TAG || t.sym.kind == S_PRIO || t.sym.kind == S_NONE){
                    Config z = new Config(c);
                    z.q = t.nextState;
                    if (t.sym.tag != 0){
                        if (z.y == null) z.y = new Tstring();
                        z.y.append(t.sym.tag);
                    }
                    if (sp >= stack.length){
                        stack = Arrays.copyOf(stack,sp+10);
                    }
                    stack[sp++] = z;
                }
            }
        }
    }

    /**
     * Convert the specified T-string into the structured LST knowing that tags in the T-string
     * have been placed surrounding each sub-expression.
     * Convert each tag into the opening or closing or leaf of its corresponding position.
     *
     * @param      str T-string
     * @return     string
     */

    private String toLST(Tstring str){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.string.length(); i++){
            int t = str.getTag(i);
            if (t == 0){
                sb.append(str.string.charAt(i));
            } else {
                if (t < 0) continue;
                if (t % 2 == 1){           // opening tag
                    sb.append("(");
                    sb.append(tagPosToString(t));
                } else {
                    AstNode ast = this.astMap[this.tagAst[t]];
                    if (ast.kind == A_LEA){
                        sb.append(tagPosToString(t));
                    }
                    sb.append(")");
                    sb.append(tagPosToString(t));
                }
            }
        }
        sb.append(EOF);
        sb.append('$');
        return sb.toString();
    }

    /**
     * Find anywhere in the specified text the longest match for the RE represented by
     * the specifed TNFA.
     *
     * @param      nfa TNFA
     * @param      str text
     * @result     matches in the Fowler format
     */

    private String findAnywhere(TNFAStateTable nfa, String str){
        this.error = false;
        List<Config> configs = new LinkedList<Config>();
        List<Config> init = new LinkedList<Config>();
        List<Config> reached = new LinkedList<Config>();
        int startmatch = -1;
        int endmatch = -1;
        boolean emptymatch = false;
        Tstring tstring = null;
        TDFAstate fake = new TDFAstate();         // fake state to trace origin closures
        loop: for (int i = 0; i < str.length(); i++){
            configs.clear();
            init.clear();
            reached.clear();
            init.add(new Config(nfa.head,null,null));
            XclosureResult res = null;
            if (this.okui){
                res = new XclosureResult();
            }
            configs = closureConf(nfa,init,configs,null,res);
            if (this.okui){
                fake.bmatrix = res.bmatrix;
            }
            for (Config j : configs){
                j.x = j.y;
                j.y = null;
            }
            int nfin = 0;
            for (Config z : configs){
                if (z.q.isFinal){
                    startmatch = i;
                    endmatch = i;
                    tstring = z.x;
                    nfin++;
                    if (nfin > 1) return null;
                    emptymatch = true;
                }
            }
            for (int j = i; j < str.length(); j++){
                char c = str.charAt(j);
                if (c >= 128){
                    this.error = true;
                    break loop;
                }
                reach(nfa,configs,c,reached);
                for (Config k : configs){
                    k.y = k.x;
                }
                configs = closureConf(nfa,reached,configs,fake,res);
                if (this.okui){
                    fake.bmatrix = res.bmatrix;
                }
                for (Config k : configs){
                    k.x.append(k.y);
                    k.y = null;
                }
                nfin = 0;
                for (Config z : configs){
                    if (z.q.isFinal){
                        startmatch = i;
                        endmatch = j;
                        tstring = z.x;
                        nfin++;
                        if (nfin > 1) return null;
                        emptymatch = false;
                    }
                }
            }
            if (endmatch >= 0) break;
        }
        // make a depth-first visit of the AST and for each group locate the tags in
        // the Tstring and compute the offsets, or better, since the tags are the same
        // as the sequence numbers, scan the Tstring and record the last occurrence of
        // them into an array

        if (endmatch < 0) return null;
        int[] offsets = new int[this.astMap.length*2];
        int off = startmatch;
        for (int i = 0; i < tstring.length() ; i++){
            int tag = tstring.getTag(i);
            if (tag != 0){
            }
            if (tag == 0){
                off++;
            } else if (tag > 0){
                offsets[tag] = off;
            } else {
                // negative tag
                offsets[-tag] = -1;
            }
        }

        int ngroups = 1;
        for (int i = 0; i < this.astMap.length; i++){
            if (this.astMap[i].isCapturing){
                ngroups++;
            }
        }
        int[] starts = new int[ngroups];
        int[] ends = new int[ngroups];
        starts[0] = startmatch;
        ends[0] = endmatch+1;
        if (emptymatch) ends[0]--;
        int n = 1;
        for (int i = 0; i < this.astMap.length; i++){
            AstNode ast = this.astMap[i];
            if (ast.isCapturing){
                starts[n] = offsets[otag(ast)];
                ends[n] = offsets[ctag(ast)];
                if (ast.kind == A_GRO){
                    if (ast.groupKind == G_OPT || ast.groupKind == G_RE0 ||
                        ast.groupKind == G_RE1 || ast.groupKind == G_RE2){
                        ast = ast.son;
                        starts[n] = offsets[otag(ast)];
                        ends[n] = offsets[ctag(ast)];
                    }
                }
                n++;
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < ngroups; i++){
            sb.append("(");
            if (starts[i] >= 0){
                sb.append(starts[i]);
            } else {
                sb.append("?");
            }
            sb.append(",");
            if (ends[i] >= 0){
                sb.append(ends[i]);
            } else {
                sb.append("?");
            }
            sb.append(")");
        }
        return sb.toString();
    }

    // ---------- TDFA -----------------

    /**
     * Compile the specified regular expression into a TDFA(0).
     *
     * @param      re string of the regular expression
     * @return     <code>true</code> if the compilation succeeded, <code>false</code> if it failed
     */

    public boolean compile(String re){
        this.error = false;

        if (this.re2c) {
            if (!this.re2c_jit) {
                this.re2c_reg = RE2C.regcomp(re, this.re2c_nfa, this.re2c_regless,
                    this.re2c_subhist, this.re2c_tstring, this.re2c_autotags);
                this.error = this.re2c_reg == 0;
            } else {
                this.re2c_re = re;
            }
            return !this.error;
        }

        init();
/*
        this.nfa = null;
        this.tdfa = null;
        this.astMap = null;
        this.astRoot = null;
        this.eofAst = null;
        this.tagHeight = null;
        this.tagAst = null;
        this.symClassTable = null;
        this.classMap = null;
        this.confTable = null;
        this.confLinks = null;
*/

        boolean res = true;
        doit: {
            buildAst(re);
            if (!this.error) this.nfa = buildTNFA(this.astRoot);
            if (getsym() != -1){              // whole re not consumed
                this.error = true;
                res = false;
                break doit;
            }
            if (!this.useTnfa){    
                this.tdfa = determinization(this.nfa,this.lookahead);
            }
        } // doit
        boolean freeast = false;
astfree: if (this.useTnfa){
    if (this.incremental){
        if (this.finreg) break astfree;
        if (!this.tagless && this.matchTstring) break astfree;
    }
    freeast = true;
}
        if (freeast){
            this.astRoot = null;
        }

        if (this.tdfa != null){
            if (!this.finreg){
                this.tagAst = null;
            }
            this.tagHeight = null;
            if (this.tagless && !this.onepass){
                this.tdfa = null;
                this.symClassTable = null;
            }
            this.path1 = null;
            this.path2 = null;
            this.paths = null;
            this.result = null;
            this.reachedConfigs = null;
            this.topsort = null;
            this.newpass = null;
            this.status = null;
            this.active = null;
            this.next = null;
            this.charbuf = null;
            this.hist1 = null;
            this.hist2 = null;
        }
        return res;
    }

    /**
     * Deliver a string representing the specified vector of registers ("v" component
     * of configurations.
     *
     * @param      v vector
     * @result     string
     */

    private String regVectorToString(int[] v){
        if (v == null) return "";
        StringBuilder sb = new StringBuilder();
        for (int i = 1; i < v.length; i++){       // tag 0 not existent
            if (v[i] == 0) continue;
            if (sb.length() > 0) sb.append(",");
            sb.append("t");
            sb.append(i);
            sb.append(":r");
            sb.append(v[i]);
        }
        return sb.toString();
    }

    /**
     * Deliver a string representing the specified vector of ordinals ("o" component
     * of configurations.
     *
     * @param      o vector
     * @result     string
     */

    private String ordinalsToString(int[] o){
        if (o == null) return "";
        StringBuilder sb = new StringBuilder();
        sb.append("<");
        for (int i = 1; i < o.length; i++){       // tag 0 not existent
            if (i > 1) sb.append(",");
            sb.append(o[i]);
        }
        sb.append(">");
        return sb.toString();
    }

    /**
     * Compare lexicographically the first array with the second one.
     *
     * @param   arr1 first array
     * @param   arr2 second array
     * @return  &lt; = or &gt; 0 if the first precedes, is equal or
     *          follows the second one
     */

    public int arraysCompare(int[] arr1, int[] arr2){
        if (arr1 == null && arr2 == null) return 0;
        if (arr1 == null) return -1;
        if (arr2 == null) return 1;
        int n = arr1.length;
        if (arr2.length < n) n = arr2.length;
        int i = 0;
        int j = 0;
        while (n-- != 0){
            int a1 = arr1[i++];
            int a2 = arr2[j++];
            if (a1 != a2) return a1 - a2;
        }
        return arr1.length - arr2.length;
    }

    /** The result of closure. */

    class XclosureResult {

        /** The set of configurations. */
        List<Config> X;

        /** The set of register operations. */
        List<Regop> regops;
        /** The maximum number of registers used. */
        int maxreg;

        /** The bmatrix, if Okui determinization. */
        int[][] bmatrix;

        /** The minimum TNFA state number (only for Okui's case and if matrices accessed with states). */
        int minTNFA;

        /** The incoming symbol. */
        int incoming;
        /**
         * Construct a closure result.
         */

        XclosureResult(){
        }

        /**
         * Construct a closure result object with the specified data.
         *
         * @param   X set of configurations
         * @param   regops set of register operations
         * @param   maxreg maximum number of registers
         */

        XclosureResult(List<Config> X,
            List<Regop> regops,
            int maxreg){
            this.X = X;
            this.regops = regops;
            this.maxreg = maxreg;
        }

        /**
         * Deliver a string representing this object.
         *
         * @return  string
         */

        public String toString(){
            return "(" + configsToString(this.X) + ",\n    " + this.regops + "," + this.maxreg + ")";
        }
    }

    /** A set of actions. */

    class TDFAaction {

        /** The vector of registers actions. */
        RegPair[] act;

        /**
         * Construct an action with the specified capacity of registers.
         *
         * @param   n capacity
         * @param   maxreg map of registers
         */

        TDFAaction(int n){
            this.act = new RegPair[n];
        }

        /**
         * Deliver a string representing this object.
         *
         * @return  string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < this.act.length; i++){
                RegPair el = this.act[i];
                if (el == null) continue;
                if (sb.length() > 0) sb.append(",");
                sb.append("r");
                sb.append(el.r1);
                sb.append("=r");
                sb.append(el.r);
                if (el.h != null && 
                    el.h.length
                    > 0){
                    sb.append("+");
                    sb.append(regbitsToString(el.h));
                }
            }
            return sb.toString();
        }

    }

    /** A TDFA arc. */

    class TDFAarc {

        /** The next arc. */
        TDFAarc next;

        /** The next state. */
        TDFAstate nextState;

        /** The symbol (character class number) that labels the arc. */
        int sym;

        /** The register actions. */
        TDFAaction zeta;

        /** The number of the arc. */
        int nrEdges;

        /**
         * Deliver a string representing this arc.
         *
         * @return  string
         */

        public String toString(){
            String str = "--";
            str += symClassTable[this.sym];
            str += "-->" + this.nextState.number;
            if (this.zeta != null){
                String fun = this.zeta.toString();
                if (fun.length() > 0) str += "," + fun;
            }
            return str;
        }
    }

    /** A TDFA state. */

    class TDFAstate {

        /** The next state. */
        TDFAstate suc;

        /** The hash link. */
        TDFAstate hlink;
        /** The set of configurations. */
        List<Config> set;

        /** Whether this state is final. */
        boolean isFinal;

        /** The list of arcs. */
        TDFAarc transList;

        /** The number of the state. */
        int number;

        /** The register initializers. */
        TDFAaction iota;

        /** The register finalizers. */
        TDFAaction eta;

        /** The B-matrix (only for Okui's case). */
        int[][] bmatrix;

        /** The minimum TNFA state number (only for Okui's case). */
        int minTNFA;

        /** The incoming symbol. */
        int incoming;
        /**
         * Deliver a string representing this state.
         *
         * @return  string
         */

        public String toString(){
            return this.number + (this.isFinal?"f ":" ") + configsToString(this.set) + " " + this.eta;
        }

        /**
         * Tell if this state contains the same data as the specified one.
         *
         * @param      d data
         * @return     <code>true</code> if it does, <code>false</code> otherwise
         */

        private boolean equals(XclosureResult d){
            boolean res = false;
            int reason = 1;
            doit: {
                if (this.set.size() != d.X.size()){
                    reason = 2;
                    break doit;
                }
                // check configurations
                Iterator<Config> i2 = d.X.iterator();
                for (Iterator<Config> i1 = this.set.iterator(); i1.hasNext();){
                    Config c1 = i1.next();
                    Config c2 = i2.next();
                    if (c1.q != c2.q){
                        reason = 3;
                        break doit;
                    }
                    if (tagless){
                        if (xcomp){
                            if (!c1.x.equals(c2.x)){
                                reason = 41;
                                break doit;
                            }
                        } else {
                            if (!Arrays.equals(c1.path,c2.path)){
                                reason = 4;
                                break doit;
                            }
                            if (finreg){
                                if (!c1.x.equals(c2.x)){
                                    reason = 41;
                                    break doit;
                                }
                            }
                        }
                    } else {
                        int tN = nrTags;
                        for (int t = 1; t <= tN; t++){
                            if (c1.o[t] != c2.o[t]) break doit;
//                            if (!op(c1.x,t).equals(op(c2.x,t))) break doit;
                            if (!opEq(c1.x,c2.x,t )) break doit;
                        }
                    }
                }

                if (okui){
                    if (this.minTNFA != d.minTNFA) {
                        reason = 5;
                        break doit;
                    }
                    if (!Arrays.deepEquals(this.bmatrix,d.bmatrix)) {
                        reason = 7;
                        break doit;
                    }
                }
                if (!autotags && (this.incoming != d.incoming)){
                    reason = 9;
                    break doit;
                }
                res = true;
            } // doit
            return res;
        }

        /**
         * Trace this state
         */

        private void trace(){
            Trc.out.printf("state: %s %s\n",this.number,this.isFinal ? " final " +
                (this.eta!=null?this.eta:"") : "");
            Trc.out.printf("  configurations:\n");
            for (Iterator<Config> i = this.set.iterator(); i.hasNext();){
                Config c = i.next();
                Trc.out.printf("    %s\n",c);
            }
            if (this.transList != null) Trc.out.printf("  arcs:\n");
            for (TDFAarc t = this.transList; t != null; t = t.next){
                Trc.out.printf("    %s %s\n",this.number,t);
            }
        }
    }

    /**
     * Deliver a string representing the specified bmatrix.
     *
     * @param      b bmatrix
     * @return     string
     */

    private String bmatrixToString(int[][] b){
        StringBuilder sb = new StringBuilder();
        sb.append("bmatrix: ");
        sb.append('[');
        for (int i = 0; i < b.length; i++){
            sb.append('[');
            for (int j = 0; j < b[i].length; j++){
                if (j > 0) sb.append(',');
                sb.append(b[i][j] & 0x7fffffff);
            }
            sb.append(']');
        }
        sb.append(']');
        sb.append(" dmatrix: ");
        sb.append('[');
        for (int i = 0; i < b.length; i++){
            sb.append('[');
            for (int j = 0; j < b[i].length; j++){
                if (j > 0) sb.append(',');
                int d = b[i][j] & 0x80000000;
                if (d < 0) d = -1;
                sb.append(d);
            }
            sb.append(']');
        }
        sb.append(']');
        return sb.toString();
    }

    /** A state table for the TDFA. */

    private class TDFAStateTable {

        /** The head of the list of states. */
        TDFAstate head;

        /** The tail of the list. */
        TDFAstate last;

        /** The last state added. */
        TDFAstate lastAdded;

        /** The hash directory. */
        TDFAstate[] hdir = new TDFAstate[64];
        /** The number of states. */
        int stateNr;

        /** The table of states. */
        TDFAstate[] table;

        /** The highest number of register allocated. */
        int maxreg;

        /** The register initializer actions. */
        TDFAaction iota;

        /** Whether the lookahead is used. */
        boolean lookahead;

        /** The number of edges. */
        int nrEdges;

        /** The transition table state,symbol -> arc-nr. */
        ComprTable transTable;

        /**
         * Search the state containing the specified data.
         *
         * @param      d data
         * @return     reference to the state, null if no such state
         */

        private TDFAstate search(XclosureResult d){
            int hvalue = 0;
            for (Config i : d.X){
                hvalue = hvalue*31 + i.q.number;
            }
            hvalue &= 0xFFFFFFF;
            hvalue %= this.hdir.length;
            for (TDFAstate h = this.hdir[hvalue]; h != null; h = h.hlink){
                if (h.equals(d)) return h;
            }
            return null;
        }

        /**
         * Add a state with the specified data, if not present.
         *
         * @param      d data
         * @return     <code>true</code> if the state is added, <code>false</code> if already present
         */

        private boolean addUnique(XclosureResult d){
            TDFAstate h = this.search(d);
            this.lastAdded = h;
            if (h != null){                           // found
                return false;
            }
            h = add(d);                               // allocate entry
            int hvalue = 0;
            for (Config i : d.X){
                hvalue = hvalue*31 + i.q.number;
            }
            hvalue &= 0xFFFFFFF;
            hvalue %= this.hdir.length;
            h.hlink = this.hdir[hvalue];              // insert at beginning
            this.hdir[hvalue] = h;                    // link to last
            h.incoming = d.incoming;
            return true;
        }

        /**
         * Add a new state.
         *
         * @param      d data
         * @return     reference to the state
         */

        private TDFAstate add(XclosureResult d){
            TDFAstate h = new TDFAstate();
            h.set = d.X;
            h.number = this.stateNr++;
            if (this.last == null) this.head = h;     // append to list
            else this.last.suc = h;
            this.last = h;
            this.lastAdded = h;
            for (Config c : d.X){
                c.inState = h;
            }
            if (okui){
                h.bmatrix = d.bmatrix;
                h.minTNFA = d.minTNFA;
            }
            return h;
        }

        /**
         * Add an arc from the specifed state with the specified symbol to the specified state.
         *
         * @param      from state
         * @param      to state
         * @param      sym symbol
         * @return     reference to the arc
         */

        private TDFAarc addArc(TDFAstate from, TDFAstate to, int sym){
            TDFAarc t = null;
            sea: {
                TDFAarc pr = null;
                for (t = from.transList; t != null; t = t.next){      // find last
                    pr = t;
                }
                t = new TDFAarc();
                t.nextState = to;
                t.sym = sym;
                if (pr == null){                // append
                    from.transList = t;
                } else {
                    pr.next = t;
                }
                this.nrEdges++;
            }
            return t;
        }

        /**
         * Trace this table of states.
         */

        private void trace(){
            if (this.iota != null){
                Trc.out.printf("register init: %s\n",this.iota.toString());
            }
            for (TDFAstate s = this.head; s != null; s = s.suc){
                s.trace();
            }
            if (!tagless){
                Trc.out.printf("final registers for tags\n");
                for (int i = 1; i <= nrTags; i++){
                    Trc.out.printf("  t%s: r%s\n",i,i+nrTags);
                }
                Trc.out.printf("maxreg %s\n",this.maxreg);
            }
            if (tagless && confLinks != null){
                Trc.out.printf("conflinks\n");
                confLinks.trace();
                Trc.out.printf("conftable\n");
                Trc.out.printf("%s\n",Arrays.toString(confTable));
            }
        }

        /**
         * Create the compacted transition tables.
         */

        public void compactTables(){
            // build the table of arcs
            this.arcsTable = new TDFAarc[this.nrEdges];
            int n = 0;
            for (TDFAstate s = this.head; s != null; s = s.suc){
                for (TDFAarc t = s.transList; t != null; t = t.next){
                    this.arcsTable[n] = t;
                    t.nrEdges = n;
                    n++;
                }
            }         
            int[][] tabs = new int[this.stateNr][];            // tables before compression
            int nsym = symClassTable.length + 1;
            // build the tables taking into account that the transitions are
            // already ordered by increasing symbol (by construction)
            for (int i = 0; i < this.stateNr; i++){
                TDFAstate s = this.table[i];
                int nval = 0;
                for (TDFAarc t = s.transList; t != null; t = t.next){
                    nval++;
                }
                tabs[i] = new int[nval*2 + 1];
                int k = 0;
                tabs[i][k++] = nsym;  // length
                for (TDFAarc t = s.transList; t != null; t = t.next){
                    tabs[i][k++] = t.sym;
                    if (tagless && !onepass){
                        tabs[i][k++] = t.nextState.number;
                    } else {
                        tabs[i][k++] = t.nrEdges;
                    }
                }
            }

            int holevalue = -1;
            CombVector comb = new CombVector(holevalue,
                CombVector.HOLES_ACCESSED |
                CombVector.FOLD_ROWS |
                CombVector.PAIRS);
            //comb.settrc("a");
            comb.merge(tabs);
            this.transTable = new ComprTable(comb,this.stateNr,nsym,ComprTable.T_INT);
            // I could use these also in match() besides match2passes ...
            this.trtable = comb.tabMerged;
            this.check = comb.check;
            this.base = comb.base;

        }

        /** The compressed table state,sym -> transition. */
        int[] trtable;

        /** The check table. */
        int[] check;

        /** The base table. */
        int[] base;

        /**
         * Deliver a string representing the transition (action) of the compact transition
         * tables for the specified state and symbol.
         *
         * @param      state number of the state
         * @param      sym symbol
         * @return     string
         */

        private String transToString(int state, int sym){
            StringBuilder str = new StringBuilder();
            int bas = this.transTable.base[state];
            int start = bas+sym;
            int ele = this.transTable.check[start] == bas ? this.transTable.mergetable[start] : this.transTable.holeValue;
            if (ele == 0) return null;
            int len = 1;
            if (ele < 0){            // array of actions
                ele = -ele;
                len = this.transTable.mergetable[ele++];
                start = ele;
            }
            for (int k = 0; k < len; k++){
                if (str.length() > 0) str.append(" ");
                int val = this.transTable.mergetable[start+k];
                str.append(val);
            }
            return str.toString();
        }

        /** The table of arcs. */
        TDFAarc[] arcsTable;

        /**
         * Deliver a string representing the graph with the states reacheable from the
         * start state.
         *
         * @return     string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            int dp = 0;
            int qp = 0;
            TDFAstate[] queue = new TDFAstate[this.stateNr];
            queue[qp++] = this.head;                    // start from it
            while (dp != qp){                           // while queue not empty
                TDFAstate s = queue[dp++];
                if (sb.length() > 0) sb.append("; ");
                sb.append(s.number);
                if (s.isFinal) sb.append("f");
                sb.append(":");
                loop: for (TDFAarc t = s.transList; t != null; t = t.next){
                    if (t != s.transList) sb.append(",");
                    sb.append(symClassTable[t.sym]);
                    sb.append("->");
                    sb.append(t.nextState.number);
                    for (int j = 0; j < qp; j++){
                        if (queue[j] == t.nextState) continue loop;  // already visited
                    }
                    queue[qp++] = t.nextState;          // enqueue it
                }
            }
            return sb.toString();
        }
    }


    /** A register operation. */

    class Regop implements Comparable {

        /** The destination register. */
        int r1;

        /** The source register. */
        int r2;

        /** The vector of bits representing the source values. */
        IntVector h;

        /**
         * Construct a register operation with the specified data.
         *
         * @param   r1 destination register
         * @param   r2 source register
         * @param   h vector of source values
         */

        Regop(int r1, int r2, IntVector h){
            this.r1 = r1;
            this.r2 = r2;
            this.h = h;
            if (h == null) this.h = new IntVector();
        }

        /**
         * Tell if this register operation is equal to the specified other one.
         *
         * @param      other the other register operation
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Object other){
            return equals((Regop)other);
        }

        /**
         * Tell if this register operation is equal to the specified other one.
         *
         * @param      other the other register operation
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Regop other){
            return this.r1 == other.r1 && this.r2 == other.r2 && this.h.equals(other.h);
        }

        /**
         * Tell if this register operation precedes, is equal or follows the specified other one,
         * comparing the components in their natural ordering.
         *
         * @param   other the other register operation
         * @return  -1 if it precedes, 0 if equal, 1 if it follows
         */

        public int compareTo(Object other){
            if (other == null) return 1;
            Regop oth = (Regop)other;
            int res = this.r1 - oth.r1;
            if (res != 0) return res;
            res = this.r2 - oth.r2;
            if (res != 0) return res;
            return this.h.compareTo(oth.h);
        }

        /**
         * Deliver a string representing this register operation.
         *
         * @return  string
         */

        public String toString(){
            String str = "(r" + this.r1 + ":r" + this.r2;
            if (this.h != null && this.h.size() > 0){
                str += "+" + regbitsToString(this.h);
            }
            str += ")";
            return str;
        }
    }

    /**
     * Deliver a string representing the specified vector of register values.
     *
     * @param   h vector
     * @return  string
     */

    private String regbitsToString(IntVector h){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < h.size(); i++){
            sb.append(h.get(i));
        }
        return sb.toString();
    }

    /**
     * Deliver a string representing the specified vector of register values.
     *
     * @param   h vector
     * @return  string
     */

    private String regbitsToString(int[] h){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < h.length; i++){
            if (this.subhist){
                if (h[i] == -2){
                    sb.append("|");
                } else {
                    sb.append(h[i]);
                }
            } else {
                sb.append(h[i]);
            }
        }
        return sb.toString();
    }

    /** A register pair. */

    class RegPair {

        /** The destination register. */
        int r1;

        /** The source register. */
        int r;

        /** The vector of bits representing the source values. */
        int[] h;
        /**
         * Construct a register pair with the specified data.
         *
         * @param   r1 destination register
         * @param   r source register
         * @param   h vector of source values
         */

        RegPair(int r1, int r, IntVector h){
            this.r1 = r1;
            this.r = r;
            this.h = h.toArray();
        }

        /**
         * Deliver a string representing this register pair.
         *
         * @return  string
         */

        public String toString(){
            return "(" + this.r1 + "=" + this.r + "+" + regbitsToString(this.h) + ")";
        }

    }
    /** A map between register operation and register numbers. */

    class Newreg {

        /** The directory of operations, by tag number. */
        NewregEl[] dir;

        /**
         * Construct a new map with the specified length.
         *
         * @param   n length
         */

        Newreg(int n){
            this.dir = new NewregEl[n];
        }

        /**
         * Add a new pair with the specified register operation and number.
         *
         * @param   o register operation
         * @param   nreg register number
         */

        void put(Newop o, int nreg){
            add(o.t,o.r,o.h,nreg);
        }

        /**
         * Add a new pair between the specified register operation data and number.
         *
         * @param   t tag number
         * @param   r register
         * @param   h vector of bits representing source values
         * @param   nreg register number
         */

        void add(int t, int r, IntVector h, int nreg){
            NewregEl el = new NewregEl();
            el.t = t;
            el.r = r;
            el.h = h;
            el.nreg = nreg;
            el.next = this.dir[t];
            this.dir[t] = el;
        }

        /**
         * Get the mapping of the specified register operation data.
         *
         * @param   t tag number
         * @param   r register
         * @param   h vector of bits representing source values
         * @return  register number
         */

        int get(int t, int r, IntVector h){
            int res = -1;
            for (NewregEl i = this.dir[t]; i != null; i = i.next){
                if (i.r == r && i.h.equals(h)){
                    res = i.nreg;
                    break;
                }
            }
            return res;
        }

        /**
         * Get the mapping of the specified register operation.
         *
         * @param   o register operation
         * @return  register number
         */

        int get(Newop o){
            return get(o.t,o.r,o.h);
        }

        /**
         * Return a string representing this object.
         *
         * @return  string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < this.dir.length; i++){
                if (this.dir[i] == null) continue;
                for (NewregEl e = this.dir[i]; e != null; e = e.next){
                    sb.append("(" + e.r + "," + e.h + ":" + e.nreg + ")");
                }
            }
            return sb.toString();
        }

        /**
         * Clear this map.
         */

        void clear(){
            Arrays.fill(this.dir,null);
        }

    }

    /** A mapping pair. */

    class NewregEl {

        /** The reference to the next in a mapping chain. */
        NewregEl next;

        /** The tag number. */
        int t;

        /** The register. */
        int r;

        /** The vector of bits representing the source values. */
        IntVector h;

        /** The mapped register number. */
        int nreg;

    }

    /** A new register operation. */

    class Newop implements Comparable {

        /** The tag number. */
        int t;

        /** The register. */
        int r;

        /** The vector of bits representing the source values. */
        IntVector h;

        /**
         * Construct a new register operation with the specified data.
         *
         * @param   h vector of source values
         */

        Newop(IntVector h){
            this.h = h;
            if (h == null) this.h = new IntVector();
        }

        /**
         * Construct a new register operation with the specified data.
         *
         * @param   t tag
         * @param   r source register
         * @param   h vector of source values
         */

        Newop(int t, int r, IntVector h){
            this.t = t;
            this.r = r;
            this.h = h;
            if (h == null) this.h = new IntVector();
        }

        /**
         * Tell if this new register operation is equal to the specified other one.
         *
         * @param      other the other new register operation
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Object other){
            return equals((Newop)other);
        }

        /**
         * Tell if this new register operation is equal to the specified other one.
         *
         * @param      other the other new register operation
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Newop other){
            return this.t == other.t && this.r == other.r && this.h.equals(other.h);
        }

        /**
         * Deliver the hash code.
         *
         * @return     hash code
         */

        public int hashCode(){
            int hash = this.t + this.r*31;
            if (this.h != null){
                int len = this.h.size();
                for (int i = 0; i < len; i++){
                    hash = 31*hash + this.h.get(i);
                }
            }
            return hash;
        }

        /**
         * Tell if this new register operation precedes, is equal or follows the specified
         * other one, comparing the components in their natural ordering.
         *
         * @param   other the other configuration
         * @return  -1 if it precedes, 0 if equal, 1 if it follows
         */

        public int compareTo(Object other){
            if (other == null) return 1;
            int res = 0;
            doit: {
                Newop oth = (Newop)other;
                res = this.t - oth.t;
                if (res != 0) break doit;
                res = this.r - oth.r;
                if (res != 0) break doit;
                res = this.h.compareTo(oth.h);
            }
            return res;
        }

        /**
         * Deliver a string representing this new register operation.
         *
         * @return  string
         */

        public String toString(){
            String str = "(t" + this.t + ":r" + this.r;
            if (this.h != null && this.h.size() > 0){
                str += "+" + regbitsToString(this.h);
            }
            str += ")";
            return str;
        }
    }

    /**
     * Deliver a string representing the specified set of configurations.
     *
     * @param   confs set
     * @return  string
     */

    private String configsToString(List<Config> confs){
        StringBuilder sb = new StringBuilder();
        if (confs != null){
            for (Config c : confs){
                if (sb.length() > 0) sb.append("\n    ");
                sb.append(c);
            }
        }
        return "[" + sb.toString() + "]";
    }

    private String confListToString(List<Config> confs){
        StringBuilder sb = new StringBuilder();
        for (Config c : confs){
            if (sb.length() > 0) sb.append(",");
            sb.append(c.id);
            if (c.inState != null) sb.append("-" + c.inState.number);
        }
        return "[" + sb.toString() + "]";
    }

    /**
     * Build a TDFA determinizing the last built TNFA with the specified lookahead.
     *
     * @param   l lookahead
     * @return  TDFA
     */

    private TDFAStateTable determinization(boolean l){
        return determinization(this.nfa,l);
    }

    /**
     * Build a TDFA determinizing the specified TNFA with the specified lookahead.
     *
     * @param   nfa TNFA
     * @param   l lookahead
     * @return  TDFA
     */


    private TDFAStateTable determinization(TNFAStateTable nfa, boolean l){
        if (this.tagless){
            TDFAStateTable dfa = determinizationTagless(nfa,l);
            return dfa;
        }

        buildSymClass();
        this.classMap = genClassMap(this.symClassTable);
        fixClassSets();

        if (!this.tagless){
            if (this.fixedTags){
                findFixedTags();
            }
        }

        // initialization
        TDFAStateTable dfa = new TDFAStateTable();
        int N = this.nrTags;
        int[] initord = new int[N+1];
        int[] initreg = new int[N+1];
        int[] finreg = new int[N+1];
        for (int t = 1; t <= N; t++){     // number of tags
            initord[t] = 0;
            initreg[t] = t;
            finreg[t] = t + N;
        }
        int maxreg = 2 * N;

        // initial closure and reg-init function
        TNFAstate q0 = nfa.head;
        Config xini = new Config(q0,initreg,initord,null,null);
        List<Config> xiniset = new LinkedList<Config>();
        xiniset.add(xini);
             // estimate
        Newreg newreg = new Newreg(this.nrTags+1);

//Trc.out.printf("--- initial state ---\n");
        XclosureResult xres = closure(nfa,l,xiniset,maxreg,newreg,null);
        //(Q0, regops, maxreg, newreg)
        List<Config> Q0 = xres.X;
        List<Regop> regops = xres.regops;
        maxreg = xres.maxreg;

        TDFAstate QQ = dfa.add(xres);
        dfa.head = QQ;
        if (!this.tagless){
            // build iota
            int n = 0;
            for (Regop i : regops){
                if (i.r1 > n) n = i.r1;
            }
            dfa.iota = new TDFAaction(n+1);
            for (Regop i : regops){
                // (r1,r2,h)
                dfa.iota.act[i.r1] = new RegPair(i.r1,i.r2,i.h);
            }
        }
        int rr = 0;

        // main loop
        TDFAstate tail = QQ;

        loop: while (QQ != null){
            TDFAstate X = QQ;
            // mark X
            // explore all outgoing transitions
            newreg.clear();
            // scan subset of character classes, which are the internal alphabet
            for (int a = 0; a < this.symClassTable.length; a++){     // each alpha in Sigma
                int alpha = a;
                List<Config> Y = new LinkedList<Config>();
                     // estimate
                reach(nfa,X.set,(char)alpha,Y);
                if (Y.isEmpty()){
                         // estimate
                    continue;
                }
                xres = closure(nfa,l,Y,maxreg,newreg,X);
                // xres: (Z,regops,maxreg,newreg)
                List<Config> Z = xres.X;
                regops = xres.regops;
//testShared(regops,"-00-");
                maxreg = xres.maxreg;
                // try to find mappable state
                TDFAstate state = null;
                int hvalue = 0;
                for (Config i : Z){
                    hvalue = hvalue*31 + i.q.number;
                }
                hvalue &= 0xFFFFFFF;
                hvalue %= dfa.hdir.length;
                fmp: for (TDFAstate Zp = dfa.hdir[hvalue]; Zp != null; Zp = Zp.hlink)
                    {
                    // if exists Z' in QQ for which regops' = map(Z',Z,T,regops) != undefined
                    List<Regop> regopsp = map(Zp,xres);
//testShared(regopsp,"-0-");
                    if (regopsp != null){
                        if (!this.tagless){
                            if (!this.bijCyclic){
                                int rop1 = regopsp.size();
                                regopsp = circularMap(regopsp);
//testShared(regopsp,"-1-");
                                if (regopsp == null){
                                    continue;
                                }
                                if (regopsp.size() != rop1){
                                    Trc.out.printf("bij %s %s re: %s\n",rop1,regopsp.size(),this.re);
                                    System.exit(1);
                                }
                            }
                        }
                        state = Zp;           //Z = Zp.set;
                        regops = regopsp;
                        for (Config u : Z){
                            for (Config v : Zp.set){
                                if (u.q == v.q){       // merge origins
                                    l: for (Config z : u.orig){
                                        for (Config w : v.orig){
                                            if (z.id == w.id) continue l;
                                        }
                                        v.orig.add(z);
                                    }
                                }
                            }
                        }
//                        break;
                        break fmp;
                    }
                } // fmp
                if (state == null){
                    // add Z to QQ
                    state = dfa.add(xres);
                    // if (dfa.stateNr == 100){
                    //     Trc.out.printf("!!!!!!\n");
                    //     break loop;
                    // }
                    tail.suc = state;
                    tail = tail.suc;
                    state.hlink = dfa.hdir[hvalue];              // insert at beginning
                    dfa.hdir[hvalue] = state;                    // link to last
                }
                // transition and reg-update functions
                TDFAarc arc = dfa.addArc(X,state,alpha);           // delta(X,alpha) = Z;
                if (!tagless){
                    rr = 0;
                    arc.zeta = new TDFAaction(regops.size());
                    for (Regop i : regops){
                        // i: (r1,r2,h)
                        arc.zeta.act[rr++] = new RegPair(i.r1,i.r2,i.h);
                    }
                }
            }
            // final state and reg-finalize function
            if (!this.tagless){
                X.eta = new TDFAaction(2*N+1);
            }
            for (Config i : X.set){
                if (!i.q.isFinal) continue;
                // exists (q,v,o,x) in X | q in F
                // add X to FF
                X.isFinal = true;
                if (!this.tagless){
                    for (int t = 1; t <= N; t++){     // foreach tag t in T
                        if (this.fixedTags){
                            if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                        }
                        IntVector rop = new IntVector();
                        op(rop,i.x,t);
                        X.eta.act[finreg[t]] = new RegPair(finreg[t],i.v[t],rop);   // (v(t),op(x,t))
                    }
                }
                break;
            }
            QQ = X.suc;
        }
        // R = {1,...,maxreg}
        dfa.maxreg = maxreg;
        dfa.lookahead = l;
        dfa.table = new TDFAstate[dfa.stateNr];
        for (TDFAstate s = dfa.head; s != null; s = s.suc){
            dfa.table[s.number] = s;
        }
        if (this.transtable){
            dfa.compactTables();
        }
        dfa.head.iota = dfa.iota;
        this.tdfa = dfa;
        if (this.tagless){
            buildLinkTables();
        }
        return dfa;          // (Sigma,T,QQ,FF,Q0,R,delta,zeta,eta,iota)
    }

boolean testShared(List<Regop> regop, String msg){
    if (regop == null) return false;
    for (Regop i : regop){
        if (i.h != null){
            for (Regop j : regop){
                if (i != j && i.h == j.h){
                    Trc.out.printf("!!! shared %s\n",msg);
                    return true;
                }
            }
        }
    }
    return false;
}

    /**
     * Find the dead configurations: the ones that have no successor in next states
     * because the configuration that they generate is discarded since not prior.
     */

    private void findDeadConfgs(){
        // mark all configs reacheable from final states
        Config[] stack = new Config[this.confSeq];
        boolean[] visited = new boolean[this.confSeq];
        int sp = 0;
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            if (!s.isFinal) continue;
            for (Config c : s.set){
                if (visited[c.id]) continue;
                stack[sp++] = c;
                while (sp > 0){                       // while stack not empty
                    c = stack[--sp];                  // pop
                    if (visited[c.id]) continue;
                    visited[c.id] = true;
                    if (c.orig == null) continue;
                    for (Config n : c.orig){
                        if (!visited[n.id]) stack[sp++] = n;
                    }
                }
            }
        }
        // visit the states and show the unmarked configs
        int n = 0;
        int tot = 0;
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            for (Config c : s.set){
                if (!visited[c.id]){
                    n++;
                }
            }
            tot += s.set.size();               
        }
        if (n > 0){
        }
    }
    /**
     * Conver the specified number of cycles to seconds.
     *
     * @param   t cycles
     * @return  seconds
     */

    private static int sec(long t){
        return (int)Math.round(t*0.45/1000000000);
    }
    private static int msec(long t){
        return (int)Math.round(t*0.45/1000000);
    }

    /**
     * Deliver a sequence of 0's and 1's representing the sequence of negative (0's) and
     * positive (1's) occurrences of the specified tag in the specified Tstring.
     *
     * @param   x Tstring
     * @param   t tag
     * @return  sequence
     */

    private IntVector op(Tstring x, int t){
        IntVector arr = new IntVector();
        op(arr,x,t);
        return arr;
    }

    private boolean opEq(Tstring x, Tstring y, int t ){
        IntVector arr1 = new IntVector();
        op(arr1,x,t);
        IntVector arr2 = new IntVector();
        op(arr2,y,t);
        boolean res = arr1.equals(arr2);
        return res;
    }

    /**
     * Collect in the specified vector a sequence of 0's and 1's representing the sequence
     * of negative (0's) and positive (1's) occurrences of the specified tag in the specified
     * Tstring.
     *
     * @param   arr vector
     * @param   x Tstring
     * @param   t tag
     * @return  sequence
     */

    private void op(IntVector arr, Tstring x, int t){
        int len = x.length();
        for (int i = 0; i < len; i++){
            int tag = x.getTag(i);
            if (this.subhist){
                // test if the tag is preceded by the opening tag of the enclosing subexpression
                int tt = tag > 0 ? tag : -tag;
                AstNode ast = this.astMap[this.tagAst[tt]];
                if (ast.fat != null && ast.fat.kind == A_GRO){
                    if (tt == t && tt % 2 == 1 && i > 0){         // opening
                        int r = x.getTag(i-1);
                        if (r < 0) r = -r;
                        AstNode enc = ast.fat;
                        if (enc != null && r == otag(enc)){
                            arr.add(-2);
                        }
                    }
                }
            }
            if (tag < 0 && tag == -t){        // -ty
                arr.add(0);
            } else if (tag > 0 && tag == t){  // ty
                arr.add(1);
            }
        }
    }

    /*
    private void op(IntVector arr, Tstring x, int t){
        if (x.length() == 0){
            return;
        } else {
            int tag = x.getTag(0);
            Tstring y = x.substring(1);
            if (tag < 0 && tag == -t){        // -ty
                arr.add(0);
                op(arr,y,t);
            } else if (tag > 0 && tag == t){  // ty
                arr.add(1);
                op(arr,y,t);
            } else {                          // ay
                op(arr,y,t);
            }
        }
    }
    */

    private String opToString(IntVector arr){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < arr.size(); i++){
            int v = arr.get(i);
            if (this.subhist){
                if (v == -2){
                    sb.append("|");
                } else {
                    sb.append(v);
                }
            } else {
                sb.append(v);
            }
        }
        return sb.toString();
    }

    /**
     * Deliver the configurations describing the paths to the states reached from the specified
     * ones with arcs labelled with tags or prios. Thread cycles only once.
     * Discard paths whose Tstrings are not prior for the current policy.
     * Build the register operations and the ordinals.
     *
     * @param      N reference to the state table
     * @param      lookahead <code>false</code> for TDFA(0), <code>true</code> for TDFA(1)
     * @param      X start configurations
     * @return     configurations describing paths to reached states
     */

    private XclosureResult closure(TNFAStateTable N, boolean lookahead, List<Config> X,
        int maxreg, Newreg newreg, TDFAstate fromState){
        XclosureResult res = new XclosureResult();
        // construct closure and update ordinals

        // List<Config> Y = new LinkedList<Config>();
        // for (Config i : X){
        //    Y.add(new Config(i.q,i.v,i.o,i.x,new Tstring(MEM("")),i));  // Y = {(q,v,o,x,epsilon) | (q,v,o,x) in X}
        // }
        for (Config i : X){
            i.y = new Tstring();
        }
        List<Config> Y = X;

        List<Config> Yp = new LinkedList<Config>();
        Y = closureConf(N,Y,Yp,fromState,res);
        List<Config> Z = Y;
        // if TDFA(0), apply lookahead operations
        if (!lookahead){
            for (Config i : Z){    // Z = {(q,v,o,y,epsilon) | (q,v,o,x,y) in Z}
                i.x = i.y;
                i.y = null;
            }
        }
        Set<Newop> newops = null;
        if (!this.tagless){
            // find all distinct operation right-hand sides
            newops = new TreeSet<Newop>();
            for (Config i : Z){                  // (q,v,o,x,y)
                int tN = this.nrTags;
                for (int t = 1; t <= tN; t++){   // all tags
                    if (this.fixedTags){
                        if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                    }
//                    IntVector h = op(i.x,t);
                    IntVector h = new IntVector();
                    op(h,i.x,t);
                    // TRACE(F,"closure -200- i: %s, %s %s %s\n",i,t,h,i.x);
                    if (h.size() > 0){           // h != epsilon
                        Newop nop = new Newop(t,i.v[t],h);
                        boolean added = newops.add(nop);
                        if (!added){
                        } else {
                        }
                        //TRACE(F,"closure -20000- %s %s %s\n",t,h,i.x);
                    } else {
                    }
                }
            }
            // allocate registers for new operations
            for (Newop o : newops){
                if (newreg.get(o) == -1){
                    maxreg++;
                    newreg.put(o,maxreg);
                    //TRACE(F,"closure -220- %s %s\n",o,maxreg);
                }
            }
            // update registers in closure
            // all closure elements have unique q-component (TNFA state) by construction,
            // so it is not possible that changing the v component an element becomes equal to
            // another

            IntVector h = new IntVector();
            for (Config i : Z){
                // (q,v,o,x,y)
                int tN = this.nrTags;
                for (int t = 1; t <= tN; t++){    // tag t in T
                    if (this.fixedTags){
                        if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                    }
                    h.clear();
                    op(h,i.x,t);
                    if (h.size() > 0){
                        i.v[t] = newreg.get(t,i.v[t],h);
                    }
                }
                //TRACE(F,"closure -222- %s\n",i);
            }
            /*
            // this scans i.x only once, but is not faster
            if (this.hist1 == null) this.hist1 = new History();
            hist.clear();
            hist.ensure(this.nrTags);
            for (Config i : Z){
                int len = i.x.length();
                for (int t = 0; t < len; t++){
                    int tag = i.x.getTag(t);
                    if (tag < 0){               // -ty
                        if (hist.h[-tag] == null) hist.h[-tag] = new IntVector();
                        hist.h[-tag].add(0);
                    } else if (tag > 0){        // ty
                        if (hist.h[tag] == null) hist.h[tag] = new IntVector();
                        hist.h[tag].add(1);
                    }
                }
                int tN = this.nrTags;
                for (int t = 1; t <= tN; t++){    // tag t in T
                    if (this.fixedTags){
                        if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                    }
                    if (hist.h[t] != null && hist.h[t].size() > 0){
                        i.v[t] = newreg.get(t,i.v[t],hist.h[t]);
//                        int ivt = i.v[t];
//                        for (NewregEl ni = newreg.dir[t]; ni != null; ni = ni.next){
//                            if (ni.r == ivt && ni.h.equals(hist.h[t])){
//                                i.v[t] = ni.nreg;
//                                break;
//                            }
//                        }
                    }
                }
            }
            */

        }

        // X = {(q,v,o,y) | (q,v,o,x,y) in Z}
        X.clear();
        for (Config z : Z){
            // X.add(new Config(z.q,z.v,z.o,z.y,z));
            X.add(z);
            z.x = z.y;
            if (z.x == null) z.x = new Tstring();
            z.y = new Tstring();
        }
        if (!this.tagless){
            List<Regop> regops = new LinkedList<Regop>();
            for (Newop o : newops){
                //TRACE(F,"closure -24- %s %s %s %s\n",o,newreg.get(o),o.r2,o.h);
                Regop ro = new Regop(newreg.get(o),o.r,o.h);
                if (!regops.contains(ro)){
                    regops.add(ro);   // o = (t,r,h) in newops
                } else {
                }
            }
            // TRACE(F,"closure -25- %s\n",regops);
            res.X = X;
            res.regops = regops;
            res.maxreg = maxreg;
        } else {
            res.X = X;
            res.regops = null;
            res.maxreg = maxreg;
        }
        // res.newreg = newreg;

        // remove intermediate configurations
        for (Config c : X){
            List<Config> l = c.getOrigins(true );
            c.orig = l;
            c.loosers = null;
        }

        return res;
    }

    private List<Config> closureConf(TNFAStateTable N, List<Config> Y, List<Config> Yp,
        TDFAstate fromState, XclosureResult res){
        if (this.posix){
            closurep(N,Y,Yp,fromState);
            if (this.okui){
                update_bmatrix(Yp,fromState,res);
                Y = Yp;
                int ord = 0;             // assign the new orders
                for (Config j : Y){
                    j.order = ord++;
                }
                // TRACE(K,"closurep done %s\n",configsToString(Y));
            } else {
                Y = Yp;
                if (this.incremental || !this.useTnfa){
                    Y = ordinals(Yp);
                }
            }
        } else {
            closure_leftmost(N,Y,Yp);
            Y = Yp;
            if (!this.tagless){
                if (this.incremental || !this.useTnfa){
                    Y = ordinals_leftmost(Yp);
                }
            }
        }
        return Y;
    }
    /**
     * Compute the ordinals across the specified set of configurations and deliver the
     * configurations with updated ordinals.
     *
     * @param      set set of configurations
     * @return     updated configurations
     */

    private List<Config> ordinals_leftmost(List<Config> set){
        int i = 0;
        // here there are values from 0.. instead if 1..., which means that there are
        // ordinals that are -1
        for (Config j : set){
            for (int k = 1; k <= this.nrTags; k++){
                j.o[k] = i;
            }
            i++;
        }
        return set;
    }

    /**
     * Map one state to the other so that the corresponding configurations
     * have equal TNFA states, ordinals and lookahead operations, and
     * there is a bijection between registers.
     *
     * @param      S one state
     * @param      O the data of the other state
     * @return     register operations needed if the mapping succeeds
     */

    private List<Regop> map(TDFAstate S, XclosureResult O)
        {
        List<Config> X = S.set;
        List<Config> Y = O.X;
        List<Regop> ops = O.regops;

        List<Regop> res = null;
        // if exists bijection M : X <-> Y , and foreach t in T exists
        // bijection m(t) : xregs(x) <-> yregs(t), such that
        // foreach((q,v,o,x), (q~,v~,o~,x~)) in M : q = q~ and o = o~ and
        // foreach t in T: op(x,t) = op(x~,t) and (v(t),v~(t)) in m(t)
        Map<Integer,Integer> m = bijection(S,O);
        if (m != null){
            // m = Union_(t in T) m(t), done in bijection
            // fix target register in existing operations
            List<Regop> ops1 = new LinkedList<Regop>();
            if (this.tagless){
                // never comes here: there is now a dedicated determinization for it
                return ops1;
            }
            for (Map.Entry<Integer,Integer> entry : m.entrySet()){
                // ops1 = {(a,c,h) | (a,b) in m and (b,c,h) in ops}
                int b = entry.getValue();
                for (Regop r : ops){
                    if (r.r1 == b){
                        Regop fixed = new Regop(entry.getKey(),r.r2,r.h);
                        if (!ops1.contains(fixed)){
                            ops1.add(fixed);
                        } else {
                        }
                        // there are no two different triples (b,c_1,h_1) and
                        // (b,c_2,h_2) for the same b since b is the
                        // newly allocated register and different registers are allocated for
                        // different right-hand sides.
                        break;
                    }
                }
            }
            // add copy operations
            List<Regop> ops2 = new LinkedList<Regop>();
            l: for (Map.Entry<Integer,Integer> entry : m.entrySet()){
                // ops2 = {(a,b,epsilon) | (a,b) in m and  a != b
                // and !exists c,h : (b,c,h) in ops}
                int b = entry.getValue();
                if (entry.getKey() == b) continue;
                for (Regop r : ops){
                    if (r.r1 == b) continue l;
                }
                Regop fixed = new Regop(entry.getKey(),b,null);
                if (!ops2.contains(fixed)){
                    ops2.add(fixed);
                } else {
                }
            }
            // ops1 union ops2
            ops1.addAll(ops2);
            res = ops1;
        } else {
            res = null;
        }
        return res;
    }

    /**
     * Build a bijection between the registers of the configurations of one state and
     * those of the other.
     *
     * @param      S one state
     * @param      O the data of the other state
     * @return     bijection
     */

    private Map<Integer,Integer> bijection(TDFAstate S, XclosureResult O){
        List<Config> X = S.set;
        List<Config> Y = O.X;
        Map<Integer,Integer> res = null;
        String reason = "";
        Map<Integer,Integer> M = null;
        Map<Integer,Integer> m = null;
        doit: {
            // 1. I assume that X and Y are ordered by the first component
            // of configurations (by TNFA state).

            // check cardinality:
            // 2. If X and Y have different number of configurations, fail.
            if (X.size() != Y.size()){
//                res = null;
                reason = "diff nr. confs";
                break doit;
            }
            // Let N be the number of configurations.
            int N = X.size();

            // check states:
            // 3. For i=1...N:
            Iterator<Config> i2 = Y.iterator();
            for (Iterator<Config> i1 = X.iterator(); i1.hasNext();){
                // 3.1. Let (q_1, v_1, o_1, x_1) be the i-th configuration in X,
                //      and (q_2, v_2, o_2, x_2) be the i-th configuration in Y.
                // 3.2. If q_1 != q_2, FAIL.
                Config c1 = i1.next();
                Config c2 = i2.next();
                if (c1.q != c2.q){
//                    res = null;
                    reason = "diff q";
                    break doit;
                }
            }

            if (this.okui){
                if (S.minTNFA != O.minTNFA){
//                    res = null;
                    reason = "diff minTNFA";
                    break doit;
                }
                if (!Arrays.deepEquals(S.bmatrix,O.bmatrix)){
//                    res = null;
                    reason = "diff bmatrix";
                    break doit;
                }
            } else {
                // check orders:
                // 4. For i=1...N:
                i2 = Y.iterator();
                for (Iterator<Config> i1 = X.iterator(); i1.hasNext();){
                    // 4.1. Let (q_1, v_1, o_1, x_1) be the i-th configuration in X,
                    //      and (q_2, v_2, o_2, x_2) be the i-th configuration in Y.
                    Config c1 = i1.next();
                    Config c2 = i2.next();
                    // 4.2. For t=1...|T|:
                    int tN = this.nrTags;
                    for (int t = 1; t <= tN; t++){
                        // 4.2.1. If o_1(t) != o_2(t), FAIL.
                        if (c1.o[t] != c2.o[t]){
//                            res = null;
                            reason = "diff o " + t + " " + c1.o[t] + " " + c2.o[t];
                            break doit;
                        }
                    }
                }
            }

            // check lookahead tag histories:
            // 5. For i=1...N:
            i2 = Y.iterator();
            for (Iterator<Config> i1 = X.iterator(); i1.hasNext();){
                // 5.1. Let (q_1, v_1, o_1, x_1) be the i-th configuration in X,
                //      and (q_2, v_2, o_2, x_2) be the i-th configuration in Y.
                Config c1 = i1.next();
                Config c2 = i2.next();
                // 5.2. For t=1...|T|:
                int tN = this.nrTags;
                for (int t = 1; t <= tN; t++){
                    // 5.2.1. If op(x_1,t) != op(x_2,t), FAIL. (where 'op' is defined on page 17)
//                    if (!op(c1.x,t).equals(op(c2.x,t))){
                    if (!opEq(c1.x,c2.x,t )){
//                        res = null;
                        reason = "diff op " + t + " " + op(c1.x,t) + " " + op(c2.x,t) + " " + c1.x + " / " + c2.x;
                        break doit;
                    }
                }
            }

            // try to construct bijection between registers:
            // 6. Let M be an empty bijective mapping between registers.
            M = new HashMap<Integer,Integer>();
            m = new HashMap<Integer,Integer>();
            if (this.tagless){
System.out.printf("!!!!! bijection tagless\n");
                return M;
            }

            // For t=1...|T|:
//int[] r2added = new int[1000];
//Arrays.fill(r2added,-1);
            int tN = this.nrTags;
            for (int t = 1; t <= tN; t++){
                // 6.1. Let m be an empty bijective mapping between registers.
                m.clear();
                // 6.2 For i=1...N:
                //TRACE(F,"bij ---- X %s\n",configsToString(X));
                //TRACE(F,"bij ---- Y %s\n",configsToString(Y));
                i2 = Y.iterator();
                for (Iterator<Config> i1 = X.iterator(); i1.hasNext();){
                    Config c1 = i1.next();
                    Config c2 = i2.next();
                    // 6.2. Let (q_1, v_1, o_1, x_1) be the i-th configuration in X,
                    //      and (q_2, v_2, o_2, x_2) be the i-th configuration in Y.
                    // Let r_1 = v_1(t), r_2 = v_2(t).
                    int r1 = c1.v[t];
                    int r2 = c2.v[t];
                    // 6.2.2. If pair (r_1, r_2) cannot be added to bijection, FAIL,
                    // otherwise add it.
                    //TRACE(F,"bij t %s c1 %s r1 %s\n",t,c1,r1);
                    Integer rmap = m.get(r1);
                    if (rmap != null && rmap != r2){
//                        res = null;
                        reason = "add bij reg failed " + r1 + " " + rmap + " != " + r2;
                        break doit;
                    } else if (rmap != null && rmap == r2){
                        continue;
                    }
                    if (m.containsValue(r2)){
//                        res = null;
                        reason = "add bij reg failed " + r2 + " duplicated mapping";
                        break doit;
                    }    

                    m.put(r1,r2);
/*
//Trc.out.printf("---!!!! put m %s %s\n",r1,r2);
if (r2added[r2] >= 0 && r2added[r2] != r1){
    Trc.out.printf("!!!! r2 %s dupl %s %s\n",r2,configsToString(X),configsToString(Y));
    Trc.out.printf("!!!! m %s\n",m);
}
r2added[r2] = r1;
*/

                    //TRACE(F,"bij r%s map to r%s\n",r1,r2);
                }
                // 6.3. Add m to M (registers of different tags do not intersect,
                //      so no possible conflict here).
                for (Map.Entry<Integer,Integer> entry : m.entrySet()){
                    M.put(entry.getKey(),entry.getValue());
                }
                //TRACE(F,"bij M %s\n",M);

                // there is already a pair (r_1, r_2) if there is already such a pair,
                // then nothing is to be done and the algorithm proceeds. However, it
                // might be that r_1 is already mapped to some r_3 which is different
                // from r_2, in which case bijection cannot be constructed. Or r_2 is
                // already mapped to something other than r_1.
            }
            // forbidding might produce some more states
            // And here I also forbid such bijections that have cycles,
            // e.g. 1 to 2, 2 to 1, because one needs a temporary
            // variable to implement swapping of two registers in C
            // key, value  value = ...  action becomes
            //             key = ...
            // thus, key must be a register that will not occur in the rhs of some actions
            res = M;
        } // doit
        if (res == null){
        }
        return res;
    }

    /**
     * Test if the specified list of registers operations contains circular operations,
     * and if it does not, then return it reordered such that any operation is not impacted
     * by the others done before it.
     *
     * @param      regopsp list of register operations
     * @return     reordered list
     */

    private List<Regop> circularMap(List<Regop> regopsp){
        LinkedList<Regop> l = new LinkedList<Regop>();
        int maxreg = 0;
        for (Iterator i = regopsp.iterator();        // determine maxreg
            i.hasNext();){
            Regop r = (Regop)i.next();
            if (r.r1 > maxreg) maxreg = r.r1;
            if (r.r2 > maxreg) maxreg = r.r2;
        }
        int[] inDegrees = new int[maxreg+1];
        for (Iterator i = regopsp.iterator();        // build the in-degrees
            i.hasNext();){
            Regop r = (Regop)i.next();
            inDegrees[r.r2]++;
        }
        // peel-off algorithm
        for (;;){
            if (regopsp.isEmpty()){
                break;                                  // success
            }
            LinkedList<Regop> visited = new LinkedList<Regop>();
            LinkedList<Regop> tovisit = new LinkedList<Regop>();
            boolean longcycles = false;
            for (Iterator j = regopsp.iterator();       // visit edges
                j.hasNext();){
                Regop r = (Regop)j.next();
                if (inDegrees[r.r1] == 0){
                    inDegrees[r.r2]--;
                    visited.add(r);
                } else {
                    tovisit.add(r);
                    if (r.r1 != r.r2){
                        longcycles = true;
                    }
                }
            }
            if (visited.isEmpty()){                     // no new edges removed: cycle
                if (longcycles){                        // there are cycles that are not auto
                    l = null;
                    break;
                }
                l.addAll(tovisit);                      // success
                break;
            }
            l.addAll(visited);
            regopsp = tovisit;
        }
        return l;
    }

    /** An order. */

    class Ord implements Comparable {

        /** The sequence number. */
        int p;

        /** The associated e_history. */
        IntVector B;

        /**
         * Construct a new order with the specified data.
         *
         * @param   p sequence number
         * @param   B e_history
         */

        Ord(int p, IntVector B){
            this.p = p;
            this.B = B;
            if (B == null) this.B = new IntVector();
        }

        /**
         * Tell if this order precedes, is equal or follows the specified other one,
         * comparing the components in descending subhistory.
         *
         * @param   other the other order
         * @return  -1 if it precedes, 0 if equal, 1 if it follows
         */

        public int compareTo(Object other){
            int res = -subhistory(this.B,((Ord)other).B);
            if (res == 0) res = this.p - ((Ord)other).p;
            return res;
        }

        /**
         * Deliver a string representing this order.
         *
         * @return  string
         */

        public String toString(){
            String str = "";
            for (int i = 0; i < this.B.size(); i++){
                if (i > 0) str += ", ";
                int v = this.B.get(i);
                if (v == INFINITE){
                    str += "\u221e";
                } else {
                    str += v;
                }
            }
            return "(" + this.p + ",[" + str + "])";
        }

        /**
         * Tell if this order is equal to the specified other one.
         *
         * @param      other the other order
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Object other){
            return equals((Ord)other);
        }

        /**
         * Tell if this order is equal to the specified other one.
         *
         * @param      other the other order
         * @return     <code>true</code> if it is, <code>false</code> otherwise
         */

        public boolean equals(Ord other){
            if (other == null) return false;
            return other.p == this.p &&
                (other.B == null ? this.B == null : other.B.equals(this.B));
        }

        /**
         * Deliver the hash code.
         *
         * @return     hash code
         */

        public int hashCode(){
            return this.p;
        }
    }

    /**
     * Compute the ordinals for the specified configurations and deliver new configurations
     * with the ordinals set in them.
     *
     * @param      set configurations
     * @return     new, updated configurations
     */

    private List<Config> ordinals(List<Config> set){
        int N = this.nrSubExpr;
        int n = set.size();
        int[][] neword = new int[n+1][];
        for (int i = 0; i < neword.length; i++){
            neword[i] = new int[this.nrTags+2];
        }
        if (2*N > this.nrTags) N = this.nrTags/2;
        for (int t = 1; t <= N; t++){
            TreeSet<Ord> ordset = new TreeSet<Ord>();
            int k = 0;
            IntVector[] B = new IntVector[n+1];
            for (Config i : set){
                IntVector[] A = e_history(i.y,2*t);
                int m = A.length;
                B[k] = A[m-1];
                if (m == 1){
                    IntVector b = new IntVector();
                    b.add(i.o[2*t]);
                    b.add(B[k]);
                    B[k] = b;
                }
                Ord o = new Ord(k,B[k]);
                ordset.add(o);
                k++;
            }
            // {(pi,Ci)} = sort {(i,Bi)} by second component using inverted <_subhistory
            // ordered by the comparator
            Ord o1 = ordset.first();
            neword[o1.p][2*t] = 0;
            int ord = 0;
            Ord prev = o1;
            k = 0;
            for (Ord i : ordset){
                if (k != 0){
                    if (!prev.B.equals(i.B)) ord++;
                    neword[i.p][2*t] = ord;
                }
                prev = i;
                k++;
            }
        }
        int k = 0;
        for (Config i : set){
            i.o = neword[k++];
        }
        return set;
    }

    /**
     * Deliver the e_history of the specified tag in the specified Tstring.
     *
     * @param      a Tstring
     * @param      t tag
     * @return     e_history
     */

    private IntVector[] e_history(Tstring a, int t){
        int i = 0;
        int j = 0;
        int n = a.string.length();
        IntVector[] arr = new IntVector[1];
        arr[0] = new IntVector();
        for (;;){
            l: for (; i < n; i++){
                int tag = a.getTag(i);
                if (tag == 0) continue;
                // for (int u = 0; u < 2*Math.ceil(t/2.0)-1; u++){
                //    if (tag == u || tag == -u) break l;
                // }

                int atag = tag > 0 ? tag : -tag;
                if (atag < 2*Math.ceil(t/2.0)-1) break;

                if (tag == t) arr[j].add(INFINITE);
                if (tag == -t) arr[j].add(-1);       // -1 = phi
            }
            if (i >= n) break;
            j++;
            if (j >= arr.length){
                arr = Arrays.copyOf(arr,j+1);
            }
            arr[j] = new IntVector();
            for (; i < n; i++){
                int tag = a.getTag(i);
                if (tag == 0) continue;
                if (tag == t || tag == -t) break;
            }
        }
        return arr;
    }

    /**
     * Compare the specified first e_history with the specifed second one.
     *
     * @param      a first e_history
     * @param      b second e_history
     * @return     -1 if the first precedes, 0 if equal, 1 if it follows the second one
     */

    private int subhistory(IntVector a, IntVector b){
        for (int i = 0; i < Math.min(a.size(),b.size()); i++){
            if (a.get(i) != b.get(i)){
                return a.get(i) > b.get(i) ? -1 : 1;
            }
        }
        return a.size() - b.size();
    }

    /**
     * Compare the specified first configuration with the specifed second one according to
     * the Posix ordering
     *
     * @param      a first configuration
     * @param      b second configuration
     * @param      fromState TDFA state from which it starts
     * @return     <code>true</code> if the first is lower than the second one, and
     *             <code>false</code> otherwise
     */

    private boolean lowerPOSIX(Config o1, Config o2, TDFAstate fromState){
        // (ox,x) (oy,y)
        boolean res = false;

        if (this.okui){
            res = compare_posix(o1,o2,fromState) < 0;
            return res;
        }
        int N = this.nrSubExpr;
        //TRACE(F,"-1- N %s n %s o %s\n",N,this.nrTags,o1.o.length);
        if (2*N > this.nrTags) N = this.nrTags/2;
        l: for (int t = 1; t <= N; t++){
            IntVector[] A = e_history(o1.y,2*t);
            int a = o1.o[2*t];
            //TRACE(R,"lowerPOSIX a %s 2*t %s ordinals %s\n",a,2*t,ordinalsToString(o1.o));
            //TRACE(F,"a %s %s t %s\n",a,o1.o.length,t);
            IntVector[] B = e_history(o2.y,2*t);
            int b = o2.o[2*t];
            //TRACE(R,"lowerPOSIX b %s 2*t %s ordinals %s\n",b,2*t,ordinalsToString(o2.o));
            //TRACE(F,"--- %s %s\n",historyToString(A),historyToString(B));
            A[0].add(0,a);
            B[0].add(0,b);
            //TRACE(F,"%s %s\n",historyToString(A),historyToString(B));
            for (int i = 0; i < A.length; i++){
                if (!A[i].equals(B[i])){
                    res = subhistory(A[i],B[i]) < 0;
                    break l;
                }
            }
        }
        return res;
    }

    /* Fixed tags
     *
     * Here is the pseudocode for the algorithm used in RE2C. It assumes a traversable TRE
     * structure passed as the first parameter RE, integer DIST (updated by the procedure,
     * an "output parameter"), tag BASE (also an "output parameter") and boolean TOPLEVEL.
     * It also assumes global arrays BASES and DISTS indexed by tags.
     * Constant VARDIST is an integer that means "the distance to the base tag is not fixed".
     * TOPLEVEL is needed because RE2C applies fixed-tags optimization only to non-nested tags.
     * Nested tags may be -1, in which case all tags that are fixed on them must also be -1.
     * This must be handled as a special case in the generated code.
     * It is possible to drop TOPLEVEL (assume that it is always true).
     *
     * find_fixed(RE, DIST, BASE, TOPLEVEL)
     *   if RE is a symbol
     *     if DIST != VARIABLE
     *       DIST = DIST + 1
     *
     *   if RE is an alternative X|Y
     *     D1 = DIST
     *     D2 = DIST
     *     find_fixed(X, D1, BASE, false)
     *     find_fixed(Y, D2, BASE, false)
     *     if D1 == D2
     *       DIST = D1
     *     else
     *       DIST = VARDIST
     *
     *   if RE is an catenation X.Y
     *     find_fixed(Y, DIST, BASE, TOPLEVEL) // note Y before X
     *     find_fixed(X, DIST, BASE, TOPLEVEL)
     *
     *   if RE is a repetition X{_,_}
     *     find_fixed(X, DIST, BASE, false) // note Y before X
     *     DIST = VARDIST
     *
     *   if RE is a tag T
     *     if TOPLEVEL and DIST != VARDIST
     *       BASES[T] = BASE
     *       DISTS[T] = DIST
     *     else if TOPLEVEL
     *       BASE = T
     *       DIST = 0
     *
     * find_fixed_tags(RE)
     *   BASES[T] = -1
     *   DISTS[T] = VARDIST
     *   DIST = 0
     *   BASE = <the tag at the rightmost end of TRE> (tag 2 for POSIX)
     *   find_fixed(RE, DIST, BASE, true)
     *
     * The optimization is split in two parts. First, find fixed tags by walking TRE AST
     * (mark them as "fixed"). Second, during determinization ignore (do not create) any
     * register operations associated with fixed tags, and add a "finalizers" that set
     * the value of a fixed tag by adding a constant offset to the value of its base tag.
     * If we record full histories, then "adding a constant to tag value" means "adding a
     * constant to each offset in history, except -1 offsets".
     */

    /** A recording object for the status of the search for fixed objects. */

    private class Fixed {

        /** The base tags. */
        int[] bases;

        /** The offsets from the tags. */
        int[] dists;

        /** The current base. */
        int base;

        /** The current distance. */
        int dist;

        /**
         * Construct a recording object.
         */

        Fixed(){
        }

        /**
         * Construct a recording object with the same contents as the other specified one.
         *
         * @param   f other recording object
         */

        Fixed(Fixed f){
            this();
            this.bases = f.bases;
            this.dists = f.dists;
            this.dist = f.dist;
            this.base = f.base;
        }

        /**
         * Deliver a string representing this object.
         *
         * @return  string
         */

        public String toString(){
            return String.format("bases %s dists %s base %s dist %s",
                Arrays.toString(bases),Arrays.toString(dists),base,dist);
        }
    }

    /** A recording object for fixed tags. */
    private Fixed fix;

    /**
     * Find the fixed tags.
     */

    private void findFixedTags(){
        if (this.fix == null){
            this.fix = new Fixed();
        }
        this.fix.bases = new int[this.nrTags+1];
        Arrays.fill(this.fix.bases,-1);
        this.fix.dists = new int[this.nrTags+1];
        Arrays.fill(this.fix.dists,-1);            // -1 = distance not fixed
        this.fix.dist = -1;
        this.fix.base = 0;
        findFixed(this.astRoot,this.fix);
    }

    /**
     * Find the fixed tags for the specified AST, recording the results in the specified object.
     *
     * @param      ast AST
     * @param      fix recording object
     */

    private void findFixed(AstNode ast, Fixed fix){
        if (this.autotags){
            int tag = otag(ast);
            if (fix.dist != -1){
                fix.bases[tag] = fix.base;
                fix.dists[tag] = fix.dist;
            } else {
                fix.base = tag;
                fix.dist = 0;
            }
        }
        switch (ast.kind){
        case A_LEA:
            if (ast.sym.kind == S_TAG){
                if (fix.dist != -1){
                    fix.bases[ast.sym.tag] = fix.base;
                    fix.dists[ast.sym.tag] = fix.dist;
                } else {
                    fix.base = ast.sym.tag;
                    fix.dist = 0;
                }
            } else if (ast.sym.kind >= S_CHAR){
                if (fix.dist != -1){
                    fix.dist++;
                }
            }
            break;
        case A_ALT:
            for (AstNode a = ast.son; a != null; a = a.bro){
                fix.dist = -1;
                Fixed f1 = new Fixed(fix);
                findFixed(a,f1);
            }
            break;
        case A_CON:
            for (AstNode a = ast.son; a != null; a = a.bro){
                findFixed(a,fix);                      // note Y before X
            }
            break;
        case A_GRO:
            // findFixed(ast.son,fix,false);           // note Y before X
            fix.dist = -1;
            Fixed f1 = new Fixed(fix);
            findFixed(ast.son,f1);
            break;
        }
        if (this.autotags){
            int tag = ctag(ast);
            if (fix.dist != -1){
                fix.bases[tag] = fix.base;
                fix.dists[tag] = fix.dist;
            } else {
                fix.base = tag;
                fix.dist = 0;
            }
        }
    }

    /** A reference to the TDFA. */
    private TDFAStateTable tdfa;

    /** The number of the first final state (when ordered). */
    private int startFinalNr;

    /** The number of the last final state (when ordered). */
    private int endFinalNr;

    /** The number of the final configuration for each final state. */
    private int[] stateFinalConfig;

    /** The compressed table state,sym -> transition. */
    int[] trtable;

    /** The check table. */
    int[] check;

    /** The base table. */
    int[] base;

    /** The tstrings of configurations. */
    char[] confTstrings;

    /** The indexes of tstrings of configurations in confTstrings. */
    int[] confPiece;

    /** The sates of configurations. */
    int[] confStates;
    /**
     * Build the TDFA for the specified RE and lookahead.
     *
     * @param      re RE
     * @param      lookahead <code>false</code> for TDFA(0), <code>true</code> for TDFA(1)
     * @return     <code>true</code> if successful, and <code>false</code> otherwise
     */

    public boolean buildTDFA(String re, boolean lookahead){
        this.error = false;
        buildAst(re);
        this.nfa = null;
        if (!this.error) this.nfa = buildTNFA(this.astRoot);
        if (getsym() != -1){              // whole re not consumed
            this.error = true;
            return false;
        }
        this.tdfa = determinization(this.nfa,lookahead);
        return true;
    }

    /** The number of bits of the register block offset. */
    static final int NSHF = 10;

    /** The block length and amount of register directory increase. */
    static final int QUANTUM = 1 << NSHF;

    /** The mask to extract the register block offset from an index. */
    static final int MSK = QUANTUM - 1;

    private static final int REG_VALUE = QUANTUM;
    /** The number of register nodes allocated. */
    int regNodeLength;

    /** The index of the first free register node. */
    int regNodeNr;

    /** The directory of the register blocks. */
    private int[][] regNodeDir;

    /** The number of fields of register elements. */
    private static final int NODE_FIELDS = 2;

    /**
     * Enlarge the register blocks so as to kave a location for the specified index.
     *
     * @param      idx register
     */

    void enlargeReg(int idx){
        int curblocks = 0;
        if (this.regNodeDir != null){
            curblocks = this.regNodeDir.length;   // length of block directories
        }
        int hiblock = (idx >>> NSHF) + 1;         // number of blocks needed
        if (hiblock > curblocks){                 // enlarge block directory
            int newblocks = hiblock;
            newblocks--;                          // ceil it to the next power of 2
            newblocks |= (newblocks >> 1);
            newblocks |= (newblocks >> 2);
            newblocks |= (newblocks >> 4);
            newblocks |= (newblocks >> 8);
            newblocks |= (newblocks >>16);
            newblocks++;
            // TRACE(M,"enlargeEdges: newblocks %d\n",newblocks);
            if (newblocks < 0){
                throw new OutOfMemoryError();
            }
            int[][] n = new int[newblocks][];
            if (this.regNodeDir != null){
                System.arraycopy(this.regNodeDir,0,n,0,curblocks);
            }
            this.regNodeDir = n;
        }
        int block = ((this.regNodeLength - 1) >> NSHF) + 1;
        while (block < hiblock){            // allocate now the blocks
            this.regNodeDir[block++] = new int[QUANTUM*NODE_FIELDS];
            if (block < 0){
                throw new OutOfMemoryError();
            }
            this.regNodeLength += QUANTUM;
        }
    }

    /**
     * Deliver a string representing the register blocks.
     *
     * @return     string
     */

    private String regBlocksToString(){
        int tot = arraySize(this.regNodeDir);
        int nodeblks = 0;
        if (this.regNodeDir != null){
            for (int i = 0; i < this.regNodeDir.length; i++){
                if (this.regNodeDir[i] == null) break;
                nodeblks++;
            }
        }
        return String.format("reg %s nodes blocks %s of %s free %s regNodeNr %s",
            tot,nodeblks,QUANTUM*NODE_FIELDS,this.regNodeLength-this.regNodeNr,
            this.regNodeNr);
    }

    private String regsToString(){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.regNodeDir[0].length; i++){
            sb.append(" " + this.regNodeDir[0][i]);
        }
        return sb.toString();
    }

    /** The index of the elements of each register. */
    private int[] regDir;

    /** The length of the value of each register. */
    private int[] regLengths;

    /** The registers. */
    private IntVector[] registers;

    /** The previous values of registers. */
    private IntVector[] registersOld;

    /** The last values of registers. */
    private int[] lastRegValues;

    /**
     * Clear the data which are not the result of compilation.
     */

    private void clear(){
        this.paths = null;
        this.path1 = null;
        this.path2 = null;
        this.result = null;
        this.topsort = null;
        this.newpass = null;
        this.status = null;
        this.visited = null;
        this.charbuf = null;
        this.reachedConfigs = null;
        this.active = null;
        this.next = null;
        this.prevBmatrix = null;
        this.partialPaths = null;
        this.partialPathsOld = null;
        this.hist1 = null;
        this.hist2 = null;
        this.fix = null;
        this.regNodeDir = null;
        this.regNodeLength = 0;
        this.regNodeNr = 0;
        this.regDir = null;
        this.regLengths = null;
        this.registers = null;
        this.registersOld = null;
        this.finalRegisters = null;
        this.lastRegValues = null;
        this.tagCurOffsets = null;
        this.treearr = null;
        this.statesSeq = null;
        this.tree = null;

this.tstrie = null;
        // result of compilation
        // eofAst, astMap, astRoot, tagHeight, tagAst, nfa, tdfa, symClassTable,
        // classMap, confTable, confLinks
        // posTable, tagPosTable, tagAltTable, tagKindTable

    }
    /**
     * Clear all data.
     */

    private void init(){
        this.paths = null;
        this.path1 = null;
        this.path2 = null;
        this.result = null;
        this.topsort = null;
        this.newpass = null;
        this.status = null;
        this.visited = null;
        this.charbuf = null;
        this.reachedConfigs = null;
        this.active = null;
        this.next = null;
        this.prevBmatrix = null;
        this.partialPaths = null;
        this.partialPathsOld = null;
        this.hist1 = null;
        this.hist2 = null;
        this.fix = null;
        this.regNodeDir = null;
        this.regNodeLength = 0;
        this.regNodeNr = 0;
        this.regDir = null;
        this.regLengths = null;
        this.registers = null;
        this.registersOld = null;
        this.finalRegisters = null;
        this.lastRegValues = null;
        this.tagCurOffsets = null;
        this.treearr = null;
        this.statesSeq = null;
        this.tree = null;

        this.eofAst = null;
        this.astMap = null;
        this.astRoot = null;
        this.tagHeight = null;
        this.tagAst = null;
        this.nfa = null;
        this.tdfa = null;
        this.symClassTable = null;
        this.classMap = null;
        this.confTable = null;
        this.confLinks = null;
        this.posTable = null;
        this.tagPosTable = null;
        this.tagAltTable = null;
        this.tagKindTable = null;
        this.stateFinalConfig = null;
        this.confTstrings = null;
        this.confStates = null;
        this.confPiece = null;
    }

    /** The number of tokens parsed. */
    private int tokens;

    /** The text to be parsed. */
    private String text;

    /**
     * Parse the specified string against this RE.
     *
     * @param      text string
     * @return     <code>true</code> if successful, and <code>false</code> otherwise
     */

private static int nrmatch;

    public boolean match(String text){
nrmatch++;
//System.out.printf("nrmatch %s\n",nrmatch);

        if (this.re2c) {
            if (this.re2c_jit) {
                this.re2c_reg = RE2C.regcomp(this.re2c_re, this.re2c_nfa,
                    this.re2c_regless, this.re2c_subhist, this.re2c_tstring, this.re2c_autotags);
                if (this.re2c_reg == 0) {
                    this.error = true;
                    return false;
                }
            }
            int e = RE2C.regexec(this.re2c_reg, text);
            if (e != 0) {
                this.error = true;
                return false;
            }
            if (this.re2c_subhist) {
                RE2C.regfreesub(this.re2c_reg);
            }
            if (this.re2c_jit) {
                RE2C.regfree(this.re2c_reg);
            }
            return true;
        }

        this.text = text;
        TDFAStateTable dfa = this.tdfa;
        this.error = false;
        this.tokens += text.length();
        this.treeLen = 0;
        if (this.useTnfa){
            transduce(text);
            if (!this.autotags && this.finreg){
                outermostOffsets();
            }

            return !this.error;
        }
        if (this.tagless){
            boolean b = false;
            if (this.onepass){
                b = matchTagless1pass(text);
            } else {
                b = matchTagless2passes(text,this.tdfa);
            }
            if (!this.autotags && this.finreg){
                outermostOffsets();
            }
            return b;
        }
        if (this.lastval){
            this.lastRegValues = new int[dfa.maxreg+1];
        } else {
            if (this.regTrie){
                if (this.bijCyclic){
                    System.out.printf("regTrie requires !bijCyclic\n");
                    System.exit(1);
                }
                if (this.regDir == null || this.regDir.length < dfa.maxreg+1){
                    if (this.regDir != null){
                    }
                    this.regDir = new int[dfa.maxreg+1];
                    this.regLengths = new int[dfa.maxreg+1];
                } else {
                    Arrays.fill(this.regDir,0);
                    Arrays.fill(this.regLengths,0);
                }
                this.regNodeNr = 1;      // 0 is reserved
                enlargeReg(1);
            } else {
                if (this.registers == null || this.registers.length < dfa.maxreg+1){
                    if (this.registers != null){
                    }
                    this.registers = new IntVector[dfa.maxreg+1];    // initialize all registers to epsilon (empty)
                }
                if (this.bijCyclic){
                    if (this.registersOld == null || this.registersOld.length < dfa.maxreg+1){
                        if (this.registersOld != null){
                        }
                        this.registersOld = new IntVector[dfa.maxreg+1];
                    }
                }
                for (int j = 0; j < dfa.maxreg+1; j++){
                    if (this.registers[j] == null){
                        this.registers[j] = new IntVector();
                    } else {
                        this.registers[j].clear();
                    }
                    if (this.bijCyclic){
                        if (this.registersOld[j] == null){
                            this.registersOld[j] = new IntVector();
                        } else {
                            this.registersOld[j].clear();
                        }
                    }
                }
            }
        }
        TDFAstate state = dfa.head;               // initial state
        boolean res = true;
        int r1 = 0;

        updreg: if (dfa.maxreg > 0){
            if (this.lastval){
                for (int j = 0; j < dfa.iota.act.length; j++){
                    if (dfa.iota.act[j] == null) continue;
                    for (int k = 0; k < dfa.iota.act[j].h.length; k++){
                        int v = dfa.iota.act[j].h[k] == 0 ? -1 : 0;
                        this.lastRegValues[j] = v;
                    }
                }
                break updreg;
            }

            for (int j = 0; j < dfa.iota.act.length; j++){
                if (!this.regTrie){
                    this.registers[j].clear();
                }
                if (dfa.iota.act[j] == null) continue;
                if (this.regTrie){
                    // guarantee that there are h.length nodes available
                    if (this.regNodeLength - this.regNodeNr < dfa.iota.act[j].h.length){
                        enlargeReg(this.regNodeNr + dfa.iota.act[j].h.length);
                    }
                    int rl = 0;
                    for (int k = 0; k < dfa.iota.act[j].h.length; k++){
                        int v = 0;
                        if (this.subhist){
                            v = dfa.iota.act[j].h[k];
                            if (v == 0) v = -1; else if (v > 0) v = 0;
                            if (v == -2 && this.regDir[j] == 0) continue;
                            rl++;
                        } else {
                            v = dfa.iota.act[j].h[k] == 0 ? -1 : 0;
                        }
                        int n = this.regNodeNr++;
                        this.regNodeDir[(n)>>>NSHF][((n)&MSK)] = this.regDir[j];
                        this.regNodeDir[(n)>>>NSHF][((n)&MSK)+REG_VALUE] = v;
                        this.regDir[j] = n;
                    }
                    if (this.subhist){
                        this.regLengths[j] += rl;
                    } else {
                        this.regLengths[j] += dfa.iota.act[j].h.length;
                    }
                } else {
                    for (int k = 0; k < dfa.iota.act[j].h.length; k++){
                        int v = 0;
                        if (this.subhist){
                            v = dfa.iota.act[j].h[k];
                            if (v == 0) v = -1; else if (v > 0) v = 0;
                            if (v == -2 && this.registers[j].size() == 0) continue;
                        } else {
                            v = dfa.iota.act[j].h[k] == 0 ? -1 : 0;
                        }
                        this.registers[j].add(v);
                    }
                }
            }
        }
        int i = 0;
        for (; i < text.length(); i++){
            if (text.charAt(i) >= 128){
                this.error = true;
                res = false;
                break;
            }
            TDFAarc arc = null;
            if (this.transtable){
                int base = dfa.transTable.base[state.number];
                int sym = this.classMap[text.charAt(i)];
                int nextarc = dfa.transTable.check[base+sym] == base ?
                    dfa.transTable.mergetable[base+sym] : dfa.transTable.holeValue;
                if (nextarc < 0){
                    this.error = true;
                    res = false;
                    break;
                }
                arc = dfa.arcsTable[nextarc];
            } else {
                for (TDFAarc t = state.transList; t!= null; t = t.next){
                    char ch = text.charAt(i);
                    if (this.classMap[ch] == t.sym){
                        arc = t;
                        break;
                    }
                }
                if (arc == null){
                    this.error = true;
                    res = false;
                    break;
                }
            }
            int cur = i;
            if (!dfa.lookahead){
                state = arc.nextState;
                cur++;
            }
            upd: if (dfa.maxreg > 0){
                if (this.lastval){
                    for (int j = 0; j < arc.zeta.act.length; j++){
                        RegPair rj = arc.zeta.act[j];
                        if (rj == null) continue;
                        for (int k = 0; k < rj.h.length; k++){
                            int v = rj.h[k] == 0 ? -1 : cur;
                            this.lastRegValues[r1] = v;
                        }
                    }
                    break upd;
                }
                if (this.bijCyclic){
                    for (int j = 0; j < this.registersOld.length; j++){
                        this.registersOld[j].clear();
                        this.registersOld[j].add(this.registers[j]);
                    }
                }
                for (int j = 0; j < arc.zeta.act.length; j++){
                    RegPair rj = arc.zeta.act[j];
                    if (rj == null) continue;
                    r1 = rj.r1;
                    if (this.bijCyclic){
                        this.registers[r1].clear();
                        this.registers[r1].add(this.registersOld[rj.r]);
                    } else {
                        if (rj.r1 != rj.r){
                            if (this.regTrie){
                                this.regDir[rj.r1] = this.regDir[rj.r];
                                this.regLengths[rj.r1] = this.regLengths[rj.r];
                            } else {
                                this.registers[rj.r1].clear();
                                this.registers[rj.r1].add(this.registers[rj.r]);
                            }
                        }
                    }
                    //TRACE(M,"update reg %s -1- %s\n",r1,this.registersOld[rj.r]);
                    if (this.regTrie){
                        // guarantee that there are h.length nodes available
                        if (this.regNodeLength - this.regNodeNr < rj.h.length){
                            enlargeReg(this.regNodeNr + rj.h.length);
                        }
                        int rl = 0;
                        for (int k = 0; k < rj.h.length; k++){
                            int v = 0;
                            if (this.subhist){
                                v = rj.h[k];
                                if (v == 0) v = -1; else if (v > 0) v = cur;
                                if (v == -2 && this.regDir[r1] == 0) continue;
                                rl++;
                            } else {
                                v = rj.h[k] == 0 ? -1 : cur;
                            }
                            int n = this.regNodeNr++;
                            this.regNodeDir[(n)>>>NSHF][((n)&MSK)] = this.regDir[r1];
                            this.regNodeDir[(n)>>>NSHF][((n)&MSK)+REG_VALUE] = v;
                            this.regDir[r1] = n;
                        }
                        if (this.subhist){
                            this.regLengths[r1] += rl;
                        } else {
                            this.regLengths[r1] += rj.h.length;
                        }
                    } else {
                        for (int k = 0; k < rj.h.length; k++){
                            int v = 0;
                            if (this.subhist){
                                v = rj.h[k];
                                if (v == 0) v = -1; else if (v > 0) v = cur;
                                if (v == -2 && this.registers[r1].size() == 0) continue;
                            } else {
                                v = rj.h[k] == 0 ? -1 : cur;
                            }
                            this.registers[r1].add(v);
                        }
                    }
                }
            }
            if (dfa.lookahead){
                state = arc.nextState;
            }
        }
        fin: if (i == text.length()){            // all text eaten
            if (!state.isFinal){
                this.error = true;
                res = false;
                break fin;
            }
            upd: if (dfa.maxreg > 0){
                if (this.lastval){
                    for (int j = 0; j < state.eta.act.length; j++){
                        RegPair rj = state.eta.act[j];
                        if (rj == null) continue;
                        for (int k = 0; k < rj.h.length; k++){
                            int v = rj.h[k] == 0 ? -1 : i;
                            this.lastRegValues[j] = v;
                        }
                    }
                    break upd;
                }
                if (this.bijCyclic){
                    for (int j = 0; j < this.registersOld.length; j++){
                        this.registersOld[j].clear();
                        this.registersOld[j].add(this.registers[j]);
                    }
                }
                for (int j = 0; j < state.eta.act.length; j++){
                    RegPair rj = state.eta.act[j];
                    if (rj == null) continue;
                    if (this.bijCyclic){
                        this.registers[j].clear();
                        this.registers[j].add(this.registersOld[rj.r]);
                    } else {
                        if (j != rj.r){
                            if (this.regTrie){
                                this.regDir[j] = this.regDir[rj.r];
                                this.regLengths[j] = this.regLengths[rj.r];
                            } else {
                                this.registers[j].clear();
                                this.registers[j].add(this.registers[rj.r]);
                            }
                        }
                    }
                    if (this.regTrie){
                        // guarantee that there are h.length nodes available
                        if (this.regNodeLength - this.regNodeNr < rj.h.length){
                            enlargeReg(this.regNodeNr + rj.h.length);
                        }
                        int rl = 0;
                        for (int k = 0; k < rj.h.length; k++){
                            int v = 0;
                            if (this.subhist){
                                v = rj.h[k];
                                if (v == 0) v = -1; else if (v > 0) v = i;
                                if (v == -2 && this.regDir[j] == 0) continue;
                                rl++;
                            } else {
                                v = rj.h[k] == 0 ? -1 : i;
                            }
                            int n = this.regNodeNr++;
                            this.regNodeDir[(n)>>>NSHF][((n)&MSK)] = this.regDir[j];
                            this.regNodeDir[(n)>>>NSHF][((n)&MSK)+REG_VALUE] = v;
                            this.regDir[j] = n;
                        }
                        if (this.subhist){
                            this.regLengths[j] += rl;
                        } else {
                            this.regLengths[j] += rj.h.length;
                        }
                    } else {
                        for (int k = 0; k < rj.h.length; k++){
                            int v = 0;
                            if (this.subhist){
                                v = rj.h[k];
                                if (v == 0) v = -1; else if (v > 0) v = i;
                                if (v == -2 && this.registers[j].size() == 0) continue;
                            } else {
                                v = rj.h[k] == 0 ? -1 : i;
                            }
                            this.registers[j].add(v);
                        }
                    }
                }
            }
        } else {
            this.error = true;
            res = false;
        }

        freg: if (res && dfa.maxreg > 0 && (this.finreg || this.matchTstring)){
            if (this.lastval) break freg;
            // having rekoned the length of the histories, here build arrays
            if (this.finalRegisters == null || this.finalRegisters.length < this.nrTags+1){
                if (this.finalRegisters != null){
                }
                this.finalRegisters = new int[this.nrTags+1][];
            }
            if (this.regTrie){
                for (i = 1; i <= this.nrTags; i++){
                    if (this.fixedTags){
                        if (this.fix.bases[i] >= 0) continue;    // tag fixed to some other
                    }
                    if (this.finalRegisters[i] != null){
                    }
                    int len = this.regLengths[i+this.nrTags];
                    int[] reg = new int[len];
                    this.finalRegisters[i] = reg;
                    int j = reg.length;
                    for (int l = this.regDir[i+this.nrTags]; l != 0; l = this.regNodeDir[(l)>>>NSHF][((l)&MSK)]){
                        reg[--j] = this.regNodeDir[(l)>>>NSHF][((l)&MSK)+REG_VALUE];
                    }
                }
            } else {
                for (i = 1; i <= this.nrTags; i++){
                    if (this.fixedTags){
                        if (this.fix.bases[i] >= 0) continue;    // tag fixed to some other
                    }
                    this.finalRegisters[i] = this.registers[i+this.nrTags].toArray();
                }
            }
            if (this.fixedTags){
                buildFixedTags();
            }
        }
        if (res && this.matchTstring){
            tagsToTstring(this.finalRegisters,text,false);
        }
        if (!this.autotags && this.finreg && !this.offsets){
            outermostOffsets();
        }
        return res;
    }

    /**
     * Build the subhistories of the fixed tags.
     */

    private void buildFixedTags(){
        for (int i = 1; i <= this.nrTags; i++){
            if (this.fix.bases[i] < 0) continue;    // tag not fixed
            int fr = i;
            if (this.offsets){
                fr = (i % 2 == 0) ? i/2 : (i-1)/2;
            }
            if (this.finalRegisters[fr] != null){
            }
            int br = this.fix.bases[i];
            if (this.offsets){
                br = (br % 2 == 0) ? br/2 : (br-1)/2;
            }
            int[] basereg = this.finalRegisters[br];
            int len = 0;
            int[] reg = null;
            if (this.subhist){
                if (i % 1 == 0){                        // closing tag
                    for (int j = 0; j < basereg.length; j++){
                        if (basereg[j] != -2) len++;
                    }
                } else {
                    len = basereg.length;
                }
                reg = new int[len];
            } else {
                if (this.offsets){
                    reg = new int[2];
                } else {
                    reg = new int[basereg.length];
                }
            }
            this.finalRegisters[fr] = reg;
            len = 0;
            for (int j = 0; j < basereg.length; j++){
                if (this.subhist){
                    if (i % 1 == 0 && basereg[j] == -2) continue;
                    reg[len] = basereg[j];
                    if (basereg[j] >= 0){
                        reg[len] += this.fix.dists[i];
                    }
                    len++;
                } else {
                    reg[j] = basereg[j];
                    if (basereg[j] >= 0){
                        reg[j] += this.fix.dists[i];
                    }
                }
            }
        }
    }

    /**
     * Add the subhistories of the outermost tags.
     */

    private void outermostOffsets(){
        if (this.finalRegisters == null){
            this.finalRegisters = new int[3][];
            this.finalRegisters[1] = new int[]{0};
            this.finalRegisters[2] = new int[]{this.text.length()};
        }
    }

    /**
     * Deliver a string representing the values of the specified register.
     *
     * @param      r register
     * @return     string
     */

    private String regToString(int r){
        StringBuilder sb = new StringBuilder();
        for (int l = this.regDir[r]; l != 0; l = this.regNodeDir[(l)>>>NSHF][((l)&MSK)]){
            if (l != this.regDir[r]) sb.insert(0," ");
            sb.insert(0,this.regNodeDir[(l)>>>NSHF][((l)&MSK)+REG_VALUE]);
        }
        return sb.toString();
    }

    /** Whether the parse tree must be generated. */
    private boolean matchTstring = true;

    /** The final values of tags. */
    private int[][] finalRegisters;

    /** The array of indexes in the offsets of tags. */
    private int[] tagCurOffsets;

    /** Temporary array to hold the tree. */
    private char[] treearr;

    /** The length of the tree. */
    private int treeLen;

    /**
     * Visit the final values of the tags and the matched string and deliver the parse tree.
     *
     * @param      registers final offsets of the tags of a match
     * @param      text string matched
     * @param      lst <code>true</code> to produce a Tstring, <code>false</code> to
     *             produce the parse tree (in Tstring format)
     * @return     Tstring if lst <code>true</code>
     */

    private Tstring tagsToTstring(int[][] registers, String text, boolean lst){
        Tstring sb = null;
        if (lst){
            sb = new Tstring();
        } else {
            // compute the size and then allocate it: it is the number of offsets that are
            // not -1 plus the length of the text providing that I store ast numbers instead
            // of characters and positions
            int len = text.length();
            for (int i = 1; i < this.nrTags+1; i++){
                for (int j = 0; j < registers[i].length; j++){
                    if (registers[i][j] >= 0) len++;
                }
            }
            if (this.treearr == null || this.treearr.length < len){
                if (this.treearr != null){
                }
                this.treearr = new char[len];
            }
            this.treeLen = 0;
        }
        // visit the AST in preorder, and at each node consume one of the corresponding tag
        // offsets; when encountering alternatives, take the one that has the offset corresponding
        // to the current input position; when encountering groups repeat as much as there are
        // offsets for the current input position

        if (this.tagCurOffsets == null || this.tagCurOffsets.length < this.nrTags+1){
            if (this.tagCurOffsets != null){
            }
            this.tagCurOffsets = new int[this.nrTags+1];
        } else {
            Arrays.fill(this.tagCurOffsets,0,this.nrTags+1,0);
        }

        // initialized to 0
        this.cursor = 0;
        if (this.subhist){
            StringBuilder sbm = new StringBuilder();
            offsetsMerge(this.astRoot,sb,registers,this.tagCurOffsets,text,lst,text.length(),sbm);
        } else {
            visitAstPreorderTree(this.astRoot,sb,registers,this.tagCurOffsets,text,lst,0);
        }
        //Trc.out.printf("built tstring %s\n",sb);
        if (lst){
            sb.append(EOF);
            sb.append('$');
        }

        return sb;
    }

    /**
     * Deliver a string of as many blanks * 2 as the argument.
     *
     * @param      lev nesting depth
     * @return     string
     */

    private String indent(int lev){
        String str = "";
        for (int i = 0; i < lev; i++){
            if (i == 0){
                str += "   ";
            } else {
                str += "|  ";
            }
        }
        return str;
    }

    /**
     * Visit the specified AST in preorder and for each node for which there is a derivation
     * in the registers deliver a piece of the tree.
     *
     * @param      ast reference to the root AST
     * @param      sb return Tstring representing the tree
     * @param      registers final offsets of the tags of a match
     * @param      tagCurOffsets offsets already used
     * @param      text string matched
     * @param      lst <code>true</code> to produce the sb Tstring, <code>false</code> to
     *             add to the parse tree
     * @param      endtag closing tag of the enclosing ast that has a tag, 0 otherwise
     */

    private void visitAstPreorderTree(AstNode ast, Tstring sb, int[][] registers,
        int[] tagCurOffsets, String text, boolean lst, int endtag){
        int tag = 0;
        if (this.autotags || ast.implicit > 0){
            tag = otag(ast);
            if (lst){
                sb.append("(");
                sb.append(posToString(ast.pos));
            } else {
                this.treearr[this.treeLen++] = intToTag(tag);
            }
            tagCurOffsets[tag]++;
            endtag = ctag(ast);
        } else {
            int endcursor = text.length();        // eat the unstructured piece
            if (endtag > 0){
                endcursor = registers[endtag][tagCurOffsets[endtag]];
            }
            while (this.cursor < endcursor){
                if (lst){
                    sb.append(text.charAt(this.cursor++));
                } else {
                    this.treearr[this.treeLen++] = text.charAt(this.cursor++);
                }
            }
            return;
        }
        switch (ast.kind){
        case A_LEA:
            if (this.cursor >= text.length()) break;
            if (lst){
                sb.append(text.charAt(this.cursor++));
                sb.append(posToString(ast.pos));
            } else {
                this.treearr[this.treeLen++] = text.charAt(this.cursor++);
            }
            break;
        case A_ALT:
            if (!this.autotags && ast.son.implicit == 0){
                visitAstPreorderTree(ast.son,sb,registers,tagCurOffsets,text,lst,ctag(ast));
                break;
            }

            for (AstNode a = ast.son; a != null; a = a.bro){
                tag = otag(a);
                if (tagCurOffsets[tag] < registers[tag].length &&
                    registers[tag][tagCurOffsets[tag]] == this.cursor){
                    if (this.negtags && this.okui){
                        // skip negative tags
                        for (AstNode an = ast.son; an != a; an = an.bro){
                            tagCurOffsets[otag(an)]++;
                        }
                    }
                    visitAstPreorderTree(a,sb,registers,tagCurOffsets,text,lst,ctag(ast));
                    if (this.negtags && this.okui){
                        // skip negative tags
                        for (AstNode an = a.bro; an != null; an = an.bro){
                            tagCurOffsets[otag(an)]++;
                        }
                    } else {
                        // remove the negative tags of the chosen alternative
                        if (this.negtags && areNegTagsExcl(ast,a)){
                            for (AstNode an = ast.son; an != null; an = an.bro){
                                if (an == a) continue;
                                negTagsSkip(an,registers,tagCurOffsets);
                            }
                        }
                    }
                    break;
                }
            }
            break;
        case A_CON:
            for (AstNode a = ast.son; a != null; a = a.bro){
                visitAstPreorderTree(a,sb,registers,tagCurOffsets,text,lst,ctag(ast));
            }
            break;
        case A_GRO:
            if (!this.autotags && ast.son.implicit == 0){
                visitAstPreorderTree(ast.son,sb,registers,tagCurOffsets,text,lst,ctag(ast));
                break;
            }
            int min = 0;
            int max = INFINITE;
            switch (ast.groupKind){
            case G_OPT: max = 1; break;
            case G_RE1: min = 1; break;
            case G_RE2:
                min = ast.lowerbound;
                if (ast.upperbound == 0){
                    max = ast.lowerbound;
                } else if (ast.upperbound > 0){
                    max = ast.upperbound;
                }
            }
            switch (ast.groupKind){
            case G_GRO:
                visitAstPreorderTree(ast.son,sb,registers,tagCurOffsets,text,lst,ctag(ast));
                break;
            case G_OPT:
            case G_RE0:
            case G_RE1:
            case G_RE2:
                tag = otag(ast.son);
                int tagc = ctag(ast.son);
                if (tagCurOffsets[tag] < registers[tag].length &&
                    registers[tag][tagCurOffsets[tag]] < 0){
                    if (this.negtags && this.okui){
                        tagCurOffsets[tag]++;
                    } else {
                        if (this.negtags && areNegTags(ast.son)){
                            negTagsSkip(ast.son,registers,tagCurOffsets);
                        }
                    }
                } else {
                    int n = 0;
                    boolean nonempty = false;
                    for (; tagCurOffsets[tag] < registers[tag].length;){
                        if (registers[tag][tagCurOffsets[tag]] > this.cursor) break;
                        if (registers[tag][tagCurOffsets[tag]] < 0) break;
                        if (tagCurOffsets[tagc] >= registers[tagc].length) break;
                        if (registers[tagc][tagCurOffsets[tagc]] < 0) break;
                        // for *,+,{} variable part, end if there had already been nonempty sons
                        // and the next one is empty
                        boolean emptyson = registers[tag][tagCurOffsets[tag]] ==
                            registers[tagc][tagCurOffsets[tagc]];
                        if (this.posix){
                            if (n >= min && nonempty && emptyson){
                                break;
                            }
                        }
                        visitAstPreorderTree(ast.son,sb,registers,tagCurOffsets,text,lst,ctag(ast));
                        n++;
                        if (n >= max) break;
                        // for *,+,{} variable part, if the son is empty, then break
                        if (this.posix){
                            if (n >= min && emptyson){
                                break;
                            }
                        }
                        nonempty = true;
                    }
                }
                break;
            }
            break;
        case A_EMP:
        case A_NUL:
            break;
        }
        if (this.autotags || ast.implicit > 0){
            tag = ctag(ast);
            if (lst){
                sb.append(")");
                sb.append(posToString(ast.pos));
            } else {
                this.treearr[this.treeLen++] = intToTag(tag);
            }
            tagCurOffsets[tag]++;
        }
    }

    /**
     * Visit the specified AST in preorder and for each node for which there is a derivation
     * in the registers deliver a piece of the tree scanning the subhistories of the
     * tags, which must contain the negative opening and closing tags and the nested negatige
     * tags as well.
     * The negative nested offsets must be in the ast order nesting.
     * The separators terminate the sequence of tags that are sons of a same tag, even when
     * they are negative.
     *
     * @param      ast reference to the root AST
     * @param      sb return Tstring representing the tree
     * @param      registers final offsets of the tags of a match
     * @param      tagCurOffsets offsets already used
     * @param      text string matched
     * @param      lst <code>true</code> to produce the sb Tstring, <code>false</code> to
     *             add to the parse tree
     * @param      endtag closing tag of the enclosing ast that has a tag, 0 otherwise
     */

    private void offsetsMerge(AstNode ast, Tstring sb, int[][] registers,
        int[] tagCurOffsets, String text, boolean lst, int endcursor, StringBuilder mrg){

        if (!this.autotags && ast.implicit == 0){
            while (this.cursor < endcursor){
                mrg.append(text.charAt(this.cursor));
                if (lst){
                    sb.append(text.charAt(this.cursor));
                } else {
                    this.treearr[this.treeLen++] = text.charAt(this.cursor);
                }
                this.cursor++;
            }
            return;
        }

        int tago = otag(ast);
        int tagc = ctag(ast);
        int sh = 0;
        if (ast.fat != null && ast.fat.kind == A_GRO){
            for (int i = tagCurOffsets[tago]; i < registers[tago].length; i++){
                if (registers[tago][i] == -2) break;
                sh++;
            }
        } else {
            sh = 1;
        }
        int[] openOff = Arrays.copyOfRange(registers[tago],tagCurOffsets[tago],tagCurOffsets[tago]+sh);
        tagCurOffsets[tago] += sh;
        int[] closeOff = Arrays.copyOfRange(registers[tagc],tagCurOffsets[tagc],tagCurOffsets[tagc]+sh);
        tagCurOffsets[tagc] += sh;
        for (int i = 0; i < sh; i++){
            mrg.append(" ");
            if (openOff[i] == -1){
                mrg.append("-");
            }
            mrg.append(tago);
            if (openOff[i] >= 0){
                if (lst){
                    sb.append("(");
                    sb.append(posToString(ast.pos));
                } else {
                    this.treearr[this.treeLen++] = intToTag(tago);
                }
            }

            switch(ast.kind){
            case A_LEA:
                if (openOff[i] == -1) break;
                if (this.cursor >= text.length()) break;
                mrg.append(text.charAt(this.cursor));
                if (lst){
                    sb.append(text.charAt(this.cursor));
                    sb.append(posToString(ast.pos));
                } else {
                    this.treearr[this.treeLen++] = text.charAt(this.cursor);
                }
                this.cursor++;
                break;
            case A_EMP:
            case A_NUL:
                break;
            default:
                for (AstNode a = ast.son; a != null; a = a.bro){
                    offsetsMerge(a,sb,registers,tagCurOffsets,text,lst,closeOff[i],mrg);
                }
            }
            mrg.append(" ");
            if (closeOff[i] == -1){
                mrg.append("-");
            }
            mrg.append(tagc);
            if (closeOff[i] >= 0){
                if (lst){
                    sb.append(")");
                    sb.append(posToString(ast.pos));
                } else {
                    this.treearr[this.treeLen++] = intToTag(tagc);
                }
            }
        }
        if (tagCurOffsets[tago] < registers[tago].length){
            if (registers[tago][tagCurOffsets[tago]] == -2){
                tagCurOffsets[tago]++;
            }
        }

    }

    private String finalToString(int[] register, int offset){
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < register.length; i++){
            if (i > 0) sb.append(", ");
            if (i == offset){
                sb.append(">");
            }
            sb.append(register[i]);
        }
        if (offset == register.length) sb.append(">");
        sb.append("]");
        return sb.toString();
    }

    /**
     * Skip the register values corresponding to the negative tags present in the specified asts.
     *
     * @param      ast reference to the root AST
     * @param      registers values of registers
     * @param      tagCurOffsets currently expended number of offsets for each register
     */

    private void negTagsSkip(AstNode ast, int[][] registers, int[] tagCurOffsets){
        int sp = 0;
        AstNode[] stack = new AstNode[10];
        stack[sp++] = ast;                        // push it
        // count the nodes
        int nrNodes = 0;
        while (sp > 0){                           // while stack not empty
            AstNode n = stack[--sp];              // pop
            nrNodes++;
            for (AstNode a = n.son; a != null; a = a.bro){
                if (sp >= stack.length){
                    stack = Arrays.copyOf(stack,sp+10);
                }
                stack[sp++] = a;                  // push it
            }
        }
        // then skip the tags
        stack[sp++] = ast;                        // push it
        while (sp > 0){                           // while stack not empty
            AstNode n = stack[--sp];              // pop
            int tag = otag(n);
            if (registers[tag][tagCurOffsets[tag]] != -1){
                Trc.out.printf("!! register error for negative tag");
            }
            tagCurOffsets[tag]++;
            tag = ctag(n);
            if (registers[tag][tagCurOffsets[tag]] != -1){
                Trc.out.printf("!! register error for negative tag");
            }
            tagCurOffsets[tag]++;
            for (AstNode a = n.son; a != null; a = a.bro){
                if (sp >= stack.length){
                    stack = Arrays.copyOf(stack,sp+10);
                }
                sp++;                             // reserve space
            }
            int p = sp;
            for (AstNode a = n.son; a != null; a = a.bro){
                stack[--p] = a;                   // push it
            }
        }
    }

    /**
     * Convert the tree T-string array into the structured LST knowing that tags in the T-string
     * have been placed surrounding each sub-expression.
     * Convert each tag into the opening or closing or leaf of its corresponding position.
     *
     * @return     string
     */

    private String toLST(){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.treeLen; i++){
            int t = 0;
            char c = this.treearr[i];
            if (c >= T_TAG){
                t = charToTag(c);
            }
            if (t == 0){
                sb.append(c);
            } else {
                if (t < 0) continue;
                if (t % 2 == 1){           // opening tag
                    sb.append("(");
                    sb.append(tagPosToString(t));
                } else {
                    if (this.tagKindTable[t] == A_LEA){
                        sb.append(tagPosToString(t));
                    }
                    sb.append(")");
                    sb.append(tagPosToString(t));
                }
            }
        }
        sb.append(EOF);
        sb.append('$');
        return sb.toString();
    }

    /**
     * Deliver the array of submatches.
     *
     * @return     array
     */

    private int[][][] submatches(){
        int[][] registers = this.finalRegisters;
        int[][][] res = new int[this.nrTags/2][][];
        int g = 0;
        for (int i = 1; i < this.nrTags; i+=2){
            int[] reg1 = registers[i];
            int[] reg2 = registers[i+1];
            int[][] pairs = new int[reg1.length][];
            res[g++] = pairs;
            for (int j = 0, k = 0; j < reg1.length; j++){
                if (reg1[j] < 0){
                    pairs[j] = new int[]{-1,-1};
                } else {
                    pairs[j] = new int[]{reg1[j],reg2[k++]};
                }
            }
        }
        return res;
    }

    /**
     * Deliver a string representing the specified submatches.
     *
     * @param      subm submatches
     * @return     string
     */

    private String submatchesToString(int[][][] subm){
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < subm.length; i++){
            sb.append("[");
            int[][] s = subm[i];
            for (int j = 0; j < s.length; j ++){
                sb.append("(");
                sb.append(s[j][0]);
                sb.append(",");
                sb.append(s[j][1]);
                sb.append(")");
            }
            sb.append("]");
        }
        sb.append("]");
        return sb.toString();
    }

    /** A set of characters. */

    static class BoolSet implements Comparable {

        /** The set: each true element is a member of the set. */
        boolean[] arr;

        /**
         * Construct an empty set.
         */

        BoolSet(){
            this.arr = new boolean[128];
        }

        /**
         * Add all the characters in the specified range to this set.
         *
         * @param   lo lower bound, included
         * @param   hi higher bound, excluded
         */

        private void addRange(int lo, int hi){
            for (int i = lo; i < hi; i++){
                this.arr[i] = true;
            }
        }

        /**
         * Assign this set with all the elements of the specified set.
         *
         * @param   b set, make of all the true elements
         */

        private void assignArr(boolean[] b){
            for (int i = 0; i < this.arr.length; i++){
                this.arr[i] = b[i];
            }
        }

        /**
         * Assign this set with all the elements of the specified set.
         *
         * @param   b set
         */

        private void assignSet(BoolSet b){
            for (int i = 0; i < this.arr.length; i++){
                this.arr[i] = b.arr[i];
            }
        }

        /**
         * Add or removes the specified element.
         *
         * @param   i index of the element
         * @param   v <code>true</code> to add the element, <code>false</code> to remove it
         */

        private void set(int i, boolean v){
            this.arr[i] = v;
        }

        /**
         * Empty this set.
         */

        private void clear(){
            Arrays.fill(this.arr,false);
        }

        /**
         * Complement this set.
         */

        private void complement(){
            for (int i = 0; i < this.arr.length; i++){
                this.arr[i] = !this.arr[i];
            }
        }

        /**
         * Add all the elements of the specified set to this set.
         *
         * @param   b set
         */

        private void or(BoolSet b){
            for (int i = 0; i < this.arr.length; i++){
                this.arr[i] |= b.arr[i];
            }
        }

        /**
         * Make the intersection of this set and the specified one.
         *
         * @param   b set
         */

        private void and(BoolSet b){
            for (int i = 0; i < this.arr.length; i++){
                this.arr[i] &= b.arr[i];
            }
        }

        /**
         * Subtracts the specified set from this one.
         *
         * @param   b set
         */

        private void sub(BoolSet b){
            for (int i = 0; i < this.arr.length; i++){
                if (b.arr[i]) this.arr[i] = false;
            }
        }

        /**
         * Tell if this set is empty.
         *
         * @return  <code>true</code> if empty, <code>false</code> otherwise
         */

        private boolean isEmpty(){
            for (int i = 0; i < this.arr.length; i++){
                if (this.arr[i]) return false;
            }
            return true;
        }

        /**
         * Tell if this set is equal to the specified one.
         *
         * @return  <code>true</code> if equal, <code>false</code> otherwise
         */

        public boolean equals(Object other){
            return equals((BoolSet)other);
        }

        /**
         * Tell if this set is equal to the specified one.
         *
         * @return  <code>true</code> if equal, <code>false</code> otherwise
         */

        public boolean equals(BoolSet other){
            return Arrays.equals(this.arr,other.arr);
        }

        /**
         * Deliver a string representing this set.
         *
         * @return  string
         */

        public String toString(){
            return symSetToString(this.arr,true);
        }

        /**
         * Tell if this set precedes, is equal or follows the specified
         * other one, comparing the elements in their natural ordering.
         *
         * @param   other the other set
         * @return  -1 if it precedes, 0 if equal, 1 if it follows
         */

        public int compareTo(Object other){
            if (other == null) return 1;
            BoolSet set = (BoolSet)other;
            boolean thisempty = this.isEmpty();
            boolean otherempty = set.isEmpty();
            if (thisempty && !otherempty) return -1;
            if (!thisempty && otherempty) return 1;
            for (int i = 0; i < this.arr.length; i++){
                if (this.arr[i] == set.arr[i]) continue;
                if (this.arr[i]) return -1;
                if (set.arr[i]) return 1;
            }
            return 0;
        }

        /**
         * Deliver a copy of this set.
         *
         * @return  copy
         */

        public BoolSet clone(){
            BoolSet b = new BoolSet();
            b.arr = Arrays.copyOf(this.arr,this.arr.length);
            return b;
        }
    }

    /** The set of character of each character subclass. */
    private BoolSet[] symClassTable;

    /**
     * Build the partition of the character classes that label the arcs of the TNFA.
     * Each element of the partition is a character subclass.
     */

    void buildSymClass(){
        BoolSet complement = new BoolSet();
        complement.addRange(0,128);
        Set<BoolSet> tempSet = new HashSet<BoolSet>();
        Set<BoolSet> classSet = new HashSet<BoolSet>();
        BoolSet curSet = new BoolSet();
        BoolSet inter = new BoolSet();
        int classNr = 0;
        for (TNFAstate h = this.nfa.head;
            h != null; h = h.suc){                      // scan all states
            for (TNFAarc t = h.transList;               // scan transitions
                t != null; t = t.next){
                if (t.sym.kind < S_CHAR) continue;
                if (t.sym.symset != null){
                    curSet.assignArr(t.sym.symset);
                } else {
                    curSet.set((int)t.sym.sym,true);
                }
                complement.sub(curSet);                 // update complement
                tempSet.clear();
                Iterator iter = classSet.iterator();
                while (iter.hasNext()){
                    BoolSet elem = (BoolSet)(iter.next());
                    if (curSet.isEmpty()) break;
                    if (curSet.equals(elem)){           // already there
                        curSet.clear();
                        break;
                    }
                    inter.assignSet(elem);
                    inter.and(curSet);
                    if (inter.isEmpty()){
                        continue;                       // no overlap
                    }
                    if (!inter.equals(elem)){           // not a superset
                        elem.sub(inter);                // remove common symbols
                        BoolSet set = inter.clone();
                        tempSet.add(set);               // insert in temporary
                    }
                    curSet.sub(inter);
                }
                if (!curSet.isEmpty()){                 // add to list
                    BoolSet set = curSet.clone();
                    tempSet.add(set);                   // insert in temporary
                }
                if (!tempSet.isEmpty()){
                    classSet.addAll(tempSet);
                }
            }
        }
        BoolSet empty = new BoolSet();
        if (!complement.isEmpty()){               // assign a class to the remaining
            classSet.add(empty);                  // placeholder for it, lowest
        }
        this.symClassTable = new BoolSet[classSet.size()];
        classSet.toArray(this.symClassTable);
        Arrays.sort(this.symClassTable);
        if (!complement.isEmpty()){               // class for all unspecified
            this.symClassTable[0] = complement;   // .. symbols always zero
        } else {
        }
    }

    /** The map that tells the number of character subclass of each character. */
    private int[] classMap;

    /* How character subclasses are used:
     *
     * char c from text
     * classMap[c] = class nr
     * t.classSet[class nr] = true if arc t matches character c
     */

    /**
     * Generate the map between character and character subclasses.
     *
     * @param      classSets character subclasses
     * @return     map
     */

    private int[] genClassMap(BoolSet[] classSets){
        int[] classMap = new int[128];
        for (int i = 0; i < classSets.length; i++){
            for (int j = 0; j < classSets[i].arr.length; j++){
                if (classSets[i].arr[j]) classMap[j] = i;       // number of subset
            }
        }
        return classMap;
    }

    /**
     * Store in each TNFA arc the sets of character subclasses that make up the character
     * class that label the arc.
     */

    private void fixClassSets(){
        for (int i = 0; i < this.nfa.table.length; i++){
            for (TNFAarc t = this.nfa.table[i].transList;   // scan transitions
                t != null; t = t.next){
                if (t.sym.kind < S_CHAR) continue;
                t.sym.cset = getClassSets(t.sym.sym,t.sym.symset);
                t.sym.kind = S_CSET;
            }
        }
    }

    /**
     * Return the set of character subclasses that make up the specified character or
     * character class.
     *
     * @param      sym single character
     * @param      symset character class
     * @return     set of subclasses
     */

    private boolean[] getClassSets(char sym, boolean[] symset){
        boolean[] res = new boolean[this.symClassTable.length];
        BoolSet cur = new BoolSet();
        BoolSet inter = new BoolSet();
        if (symset != null){
            cur.assignArr(symset);
        } else {
            cur.set((int)sym,true);
        }
        for (int i = 0;                               // find subclasses which
            i < this.symClassTable.length; i++){      // .. make up the set
            inter.assignSet(this.symClassTable[i]);   // .. of this transition
            inter.and(cur);
            if (!inter.isEmpty()){                    // found a subset component of the current one
                res[i] = true;
                cur.sub(inter);
                if (cur.isEmpty()) break;
            }
        }
        return res;
    }

    // ---------- Tagless matching and building of parse trees  -----------------

    /**
     * Build a TDFA determinizing the specified TNFA with the specified lookahead.
     * Version specific for tagless matching.
     *
     * @param   nfa TNFA
     * @param   l lookahead
     * @return  TDFA
     */

    private TDFAStateTable determinizationTagless(TNFAStateTable nfa, boolean l){
        buildSymClass();
        this.classMap = genClassMap(this.symClassTable);
        fixClassSets();
        if (this.fixedTags){
            this.findFixedTags();
        }
        // initialization
        TDFAStateTable dfa = new TDFAStateTable();
        this.tdfa = dfa;
        int N = this.nrTags;
        // initial closure
        TNFAstate q0 = nfa.head;
        Config xini = new Config(q0,null,null,null,null,null);
        List<Config> xiniset = new LinkedList<Config>();
        xiniset.add(xini);
             // estimate
        XclosureResult xres = closure(nfa,l,xiniset,0,null,null);
xres.incoming = -1;
        List<Config> Q0 = xres.X;
        TDFAstate QQ = dfa.add(xres);
        dfa.head = QQ;
        // main loop
        loop: while (QQ != null){
            TDFAstate X = QQ;
            // explore all outgoing transitions
            // scan subset of character classes, which are the internal alphabet
            for (int a = 0; a < this.symClassTable.length; a++){     // each alpha in Sigma
                int alpha = a;
                List<Config> Y = new LinkedList<Config>();
                     // estimate
                reach(nfa,X.set,(char)alpha,Y);
                if (Y.isEmpty()){
                         // estimate
                    continue;
                }
                xres = closure(nfa,l,Y,0,null,X);
xres.incoming = alpha;
                List<Config> Z = xres.X;
                // search if there is a state that has the same set of configs
                boolean added = dfa.addUnique(xres);
                TDFAstate state = dfa.lastAdded;
                if (added){
                } else {
                    // found
                    for (Config u : Z){
                        for (Config v : state.set){
                            if (u.q == v.q){       // merge origins
                                l: for (Config z : u.orig){
                                    for (Config w : v.orig){
                                        if (z.id == w.id) continue l;
                                    }
                                    v.orig.add(z);
                                }
                            }
                        }
                    }
                }
                TDFAarc arc = dfa.addArc(X,state,alpha);           // delta(X,alpha) = Z;
            }
            for (Config i : X.set){
                if (!i.q.isFinal) continue;
                X.isFinal = true;
            }
            QQ = X.suc;
        }
        dfa.lookahead = l;

        // count the number of final states
        int finnr = 0;
        for (TDFAstate s = dfa.head; s != null; s = s.suc){
            if (s.isFinal) finnr++;
        }
        // renumber the states: 0 is always the initial one, then there are all the
        // final ones (except the initial one, if also final), and then all the others
        int stidx = finnr + 1;         // initial number for the non-final, non-inital ones
        this.startFinalNr = 1;         // initial number of final states
        if (dfa.head.isFinal){
            stidx--;          
            this.startFinalNr = 0;
        }
        int stfin = 1;
        for (TDFAstate s = dfa.head.suc; s != null; s = s.suc){
            if (s.isFinal){
                s.number = stfin++;
            } else {
                s.number = stidx++;
            }
        }
        this.endFinalNr = stfin - 1;   // final number for final states
        // then, to know if a state is final: startFinalNr <= n <= endFinalNr

        dfa.table = new TDFAstate[dfa.stateNr];
        for (TDFAstate s = dfa.head; s != null; s = s.suc){
            dfa.table[s.number] = s;
        }
        if (this.transtable){
            dfa.compactTables();
            this.trtable = dfa.trtable;
            this.check = dfa.check;
            this.base = dfa.base;
        }
        buildLinkTables();
        this.stateFinalConfig = new int[this.endFinalNr+1];
        for (TDFAstate s = dfa.head; s != null; s = s.suc){
            if (s.isFinal){
                Config fc = null;
                for (Config c : s.set){
                    if (c.q.isFinal){
                        if (fc != null){
                            System.out.printf("!! several final configs\n");
                        }
                        fc = c;
                    }
                }
                this.stateFinalConfig[s.number] = fc.id;
            }
        }
        //Trc.out.printf("!!! nr states %s\n",dfa.stateNr);
        //Trc.out.printf("nrLower %s\n",this.nrLower);
//        FREEMEM("determ",initord);
        return dfa;          // (Sigma,T,QQ,FF,Q0,R,delta,zeta,eta,iota)
    }

    /**
     * Build the tables that link configurations in a state with the ones in previous states.
     *
     * @return    tables
     */

    /* It builds a table that is indexed with a configuration id and a state number and tells the
     * predecessor configuration (giving its id).
     * With partial parsing it happens that a state S can reach a state T with two different
     * input symbols. In such a case there could be two configurations of S that generate a
     * same configuration in T, leading thus to a link conflict.
     * The incoming input symbol is then recorded in states so that two states can be equal
     * only if the incoming input symbols are the same.
     * With full parsing this does not occur because each input symbol is followed by its
     * closing tag, and thus it ends in a TNFA state that is not shared with others, and the
     * closure is done on it.
     */

    private void buildLinkTables(){
        purgeConfigs();                                    // remove useless configurations
// an array can hold the data of the configs for match(): .q, .x or .path
// 2 chars for .q and then a length and .x or .path, or better, 2 arrays
// measure it here
        int plen = 0;
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            for (Config c : s.set){
                if (this.xcomp){
                    plen += c.x.length();
                } else {
                    if (this.finreg){
                        plen += c.x.length();
                    } else {
                        plen += c.path.length;
                    }
                }
                plen++;     // length
            }
        }
        this.confTstrings = new char[plen];
        plen = 0;
        this.confStates = new int[this.confSeq];
        this.confPiece = new int[this.confSeq];
        int[][] tabs = new int[this.confSeq][];            // tables before compression
        Config[] row = new Config[this.tdfa.stateNr];
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            for (Config c : s.set){
                this.confPiece[c.id] = plen;
                int ln = 0;
                if (this.xcomp){
                    ln = c.x.length();
                    this.confTstrings[plen++] = (char)ln;
                    c.x.copy(this.confTstrings,plen);
                } else {
                    if (this.finreg){
                        ln = c.x.length();
                        this.confTstrings[plen++] = (char)ln;
                        c.x.copy(this.confTstrings,plen);
                    } else {
                        ln = c.path.length;
                        this.confTstrings[plen++] = (char)ln;
                        System.arraycopy(c.path,0,this.confTstrings,plen,ln);
                    }
                }
                plen += ln;
                this.confStates[c.id] = c.q.number;
                // build the row of the table in increasing state number
                Arrays.fill(row,null);
                List<Config> l = c.getOrigins(true );
                int len = 0;
                for (Config i : l){
                    if (i.inState != null){
                        dupl: if (row[i.inState.number] != null){
                        }
                        row[i.inState.number] = i;
                        len++;
                    }
                }
                if (len == 0) continue;                
                int nval = 0;
                tabs[c.id] = new int[len*2 + 1];
                int k = 0;
                tabs[c.id][k++] = this.tdfa.stateNr;  // length
                for (int i = 0; i < row.length; i++){
                    Config o = row[i];
                    if (o == null) continue;
                    tabs[c.id][k++] = o.inState.number;
                    tabs[c.id][k++] = o.id;
                }
            }
        }
        // create the missing ones
        for (int i = 0; i < tabs.length; i++){
            if (tabs[i] == null){
                tabs[i] = new int[]{this.tdfa.stateNr};
            }
        }

        int holevalue = -1;
        CombVector comb = new CombVector(holevalue,
            CombVector.HOLES_ACCESSED |
            CombVector.FOLD_ROWS |
            CombVector.PAIRS);
        //comb.settrc("a");
        comb.merge(tabs);
        this.confLinks = new ComprTable(comb,this.confSeq,this.tdfa.stateNr,ComprTable.T_INT);
    }
    /** The configuration links to predecessors table. */
    ComprTable confLinks;

    /** The table of configurations. */
    Config[] confTable;

    /**
     * Remove the configurations that cannot be reached from the final ones threading
     * their origin one in previous states.
     */

    private void purgeConfigs(){
        // mark the final ones and the ones linked to them and that belong to states
        Config[] confTable = new Config[this.confSeq];
        Config[] stack = new Config[this.confSeq];
        int sp = 0;
        boolean[] visited = new boolean[this.confSeq];
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            if (!s.isFinal) continue;
            for (Config c : s.set){
                if (!c.q.isFinal) continue;
                stack[sp++] = c;
            }
        }
        while (sp > 0){
            Config c = stack[--sp];
            if (visited[c.id]) continue;
            visited[c.id] = true;
            confTable[c.id] = c;
            List<Config> l = c.getOrigins(true );
            //TRACE(F,"purgeConfigs origins %s\n",confListToString(l));
            for (Config i : l){
                if (i.inState != null){
                    if (!visited[i.id]) stack[sp++] = i;
                }
            }
        }
        // renumber them and remove the non-marked ones
        int seq = 0;
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            List<Config> nc = new LinkedList<Config>();
            for (Config c : s.set){
                if (!visited[c.id]){
                    continue;
                }
                nc.add(c);
            }
            s.set = nc;
        }
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            for (Config c : s.set){
                List<Config> no = new LinkedList<Config>();
                List<Config> l = c.getOrigins(true );
                for (Config i : l){
                    if (i.inState == null) continue;
                    no.add(i);
                }
                c.orig = no;
            }
        }
        for (TDFAstate s = this.tdfa.head; s != null; s = s.suc){
            for (Config c : s.set){
                c.id = seq++;
            }
        }

        this.confSeq = seq;
    }

    /**
     * Parse the specified string against this RE without using tags and collecting the
     * final Tstring or tag histories with a backward pass.
     *
     * @param      text string
     * @return     <code>true</code> if successful, and <code>false</code> otherwise
     */

    public boolean matchTagless2passes(String text, TDFAStateTable dfa){
        this.tokens += text.length();
        this.error = false;
        int state = 0;
        int len = text.length();

        if (this.statesSeq == null || this.statesSeq.length < len+1){
            if (this.statesSeq != null){
            }
            this.statesSeq = new int[len+1];
        }
        this.statesSeq[0] = 0;
        int seq = 1;

        for (int i = 0; i < len; i++){
            char c = text.charAt(i);
            if (c > 128){
                this.error = true;
                break;
            }
            int base = this.base[state];
            int symbase = this.classMap[c] + base;
            state = this.check[symbase] == base ? this.trtable[symbase] : -1;
            if (state < 0){
                this.error = true;
                return false;
            }
            this.statesSeq[seq++] = state;
        }
        if (state < this.startFinalNr || this.endFinalNr < state)
        {
            this.error = true;
            // not recognized
        } else if (this.matchTstring || this.finreg || this.parsetree){
            // we have now the sequence of states: build the Tstring tracing back the configurations
            // find the final config
            int fc = this.stateFinalConfig[state];
            int[] saveStatesSeq = null;
            if (this.matchTstring){
                if (this.finreg){
                    if (this.subhist){
                        computeTstring(fc,text);
                        computeHistoriesTstring();
                    } else {
                        saveStatesSeq = Arrays.copyOf(this.statesSeq,this.statesSeq.length);
                        computeTstring(fc,text);
                        this.statesSeq = saveStatesSeq;
                    }
                } else {
                    if (this.parsetree){
                        saveStatesSeq = Arrays.copyOf(this.statesSeq,this.statesSeq.length);
                    }
                    computeTstring(fc,text);
                }
            }
            if (this.subhist){
                if (!this.matchTstring && this.finreg){
                    if (this.parsetree){
                        saveStatesSeq = Arrays.copyOf(this.statesSeq,this.statesSeq.length);
                    }
                    computeTstring(fc,text);
                    computeHistoriesTstring();
                }
            } else {
                if (this.finreg){
                    computeHistories(fc,text,true);
                }
            }

            if (this.parsetree){
                if (saveStatesSeq != null){
                    this.statesSeq = saveStatesSeq;
                }
                buildTree(fc,this.text);
            }
        }
        return !this.error;
    }

    /** The sequence of states. */
    private int[] statesSeq;

    /**
     * Compute the Tstring from the chain of configurations.
     *
     * @param      fc head of the chain
     * @param      text matched string
     */

    /*
     * There are these solutions to build the Tstring, starting with the final configuration
     * and visiting the chain of configurations:
     *
     *   1. to compute first the length and then allocate the tree (or ensure it has room enough)
     *      in a backwards pass and then fill it from the end in a forward pass
     *   2. to prepend to the tree
     *   3. to compute online the length in the recognizion pass
     *
     * Prepending requires a lot of shifts, and computing online requires several operations
     * for each state, so the first solution is chosen.
     * To get the proper Tstring we must store the input characters, not the character classes.
     * The path fragments are recorded in configurations as Tstrings in array form so as to be
     * able to copy them easily in the tree array.
     * We reuse the array for the sequence of states to store the state numbers when matching,
     * and in the backward pass to keep configuration numbers (while calculating the length of
     * the treearr); this avoids to access the configuration link table a second time.
     */

    private void computeTstring(Config fc, String text){
        // measure the LST
        int i = text.length();
        int len = 0;
        for (Config c = fc; c != null;){
            if (this.subhist){
                if (this.xcomp){
                    len += c.x.length();
                } else {
                    if (this.finreg){
                        len += c.x.length();
                    } else {
                        len += c.path.length;
                    }
                }
            } else {
                len += c.path.length;
            }
            if (i == 0) break;
            int bas = this.confLinks.base[c.id];
            int start = bas+this.statesSeq[--i];
            int ele = this.confLinks.mergetable[start];
            c = this.confTable[ele];
            this.statesSeq[i] = ele;          // record in it the config number
            len++;
        }
        // allocate it
        if (this.treearr == null || this.treearr.length < len){
            if (this.treearr != null){
            }
            this.treearr = new char[len];
        }
        this.treeLen = len;

        // then fill it
        i = 0;
        len = text.length();
        for (int j = 0; j < len; j++){
            Config c = this.confTable[this.statesSeq[j]];
            if (this.subhist){
                if (this.xcomp){
                    c.x.copy(this.treearr,i);
                    i += c.x.length();
                    this.treearr[i++] = text.charAt(j);
                } else {
                    if (this.finreg){
                        for (int k = 0; k < c.x.length(); k++){
                            this.treearr[i++] = c.x.charAt(k);
                        }
                        this.treearr[i++] = text.charAt(j);
                    } else {
                        System.arraycopy(c.path,0,this.treearr,i,c.path.length);
                        i += c.path.length;
                        this.treearr[i++] = text.charAt(j);
                    }
                }
            } else {
                System.arraycopy(c.path,0,this.treearr,i,c.path.length);
                i += c.path.length;
                this.treearr[i++] = text.charAt(j);
            }
        }
        if (this.subhist){
            if (this.xcomp){
                fc.x.copy(this.treearr,i);
            } else {
                if (this.finreg){
                    for (int k = 0; k < fc.x.length(); k++){
                        this.treearr[i++] = fc.x.charAt(k);
                    }
                } else {
                    System.arraycopy(fc.path,0,this.treearr,i,fc.path.length);
                }
            }
        } else {
            System.arraycopy(fc.path,0,this.treearr,i,fc.path.length);
        }
    }


    private void computeTstring(int fc, String text){
        // measure the LST
        int i = text.length();
        int len = 0;
        for (int c = fc; c >= 0;){
            int piece = this.confPiece[c];
            len += this.confTstrings[piece];
            if (i == 0) break;
            int bas = this.confLinks.base[c];
            int start = bas+this.statesSeq[--i];
            int ele = this.confLinks.mergetable[start];
            // this means that config 0 means null
            c = ele;
            this.statesSeq[i] = ele;          // record in it the config number
            len++;
        }
        // allocate it
        if (this.treearr == null || this.treearr.length < len){
            if (this.treearr != null){
            }
            this.treearr = new char[len];
        }
        this.treeLen = len;

        // then fill it
        i = 0;
        len = text.length();
        for (int j = 0; j < len; j++){
            int c = this.statesSeq[j];
            int piece = this.confPiece[c];
            int ln = this.confTstrings[piece];
            System.arraycopy(this.confTstrings,piece+1,this.treearr,i,ln);
            i += ln;
            this.treearr[i++] = text.charAt(j);
        }
        int piece = this.confPiece[fc];
        System.arraycopy(this.confTstrings,piece+1,this.treearr,i,this.confTstrings[piece]);
    }
    /**
     * Compute the histories (aka final registers) from the chain of configurations.
     *
     * @param      fc head of the chain
     * @param      text matched string
     * @param      dfa <code>true</code> if it works for a TDFA, <code>false</code> if for a TNFA
     */

    private void computeHistories(Config fc, String text, boolean tdfa){
        // another representation is with an array that contains lists of histories: working
        // backwards I could allocate a list element each time an offset is added and make it
        // point to from a directory; all other offsets are prepended

        if (this.finalRegisters == null || this.finalRegisters.length < this.nrTags+1){
            if (this.finalRegisters != null){
            }
            this.finalRegisters = new int[this.nrTags+1][];
        }
        // compute the length of each history
        int[] lengths = new int[this.nrTags+1];
        int i = text.length();
        for (Config c = fc; c != null;){
            for (int j = c.x.length()-1; j >= 0; j--){
                int p = c.x.charAt(j);
                int t = (p >= T_NTAG) ? (p - T_NTAG) : (p - T_TAG);
                lengths[t]++;                    
            }
            if (i == 0) break;
            if (tdfa){
                int bas = this.confLinks.base[c.id];
                int start = bas+this.statesSeq[--i];
                int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
                c = this.confTable[ele];
            } else {
                List<Config> l = c.getOrigins(true );
                int n = 0;
                for (Config z : l){
                    if (z.inState != null){
                        n++;
                        c = z;
                    }
                }
                if (n > 1){
                } else if (n == 0){
                    c = null;
                }
            }
        }
        // allocate then each history
        for (int j = 1; j < lengths.length; j++){
            if (this.finalRegisters[j] != null){
            }
            this.finalRegisters[j] = new int[lengths[j]];
        }
        // fill then each history
        i = text.length();
        for (Config c = fc; c != null;){
            for (int j = c.x.length()-1; j >= 0; j--){
                int p = c.x.charAt(j);
                if (p >= T_NTAG){
                    int t = p - T_NTAG;
                    this.finalRegisters[t][--lengths[t]] = -1;
                } else {
                    int t = p - T_TAG;
                    this.finalRegisters[t][--lengths[t]] = i;
                }
            }
            if (i == 0) break;
            if (tdfa){
                int bas = this.confLinks.base[c.id];
                int start = bas+this.statesSeq[--i];
                int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
                c = this.confTable[ele];
            } else {
                List<Config> l = c.getOrigins(true );
                int n = 0;
                for (Config z : l){
                    if (z.inState != null){
                        n++;
                        c = z;
                    }
                }
                if (n > 1){
                } else if (n == 0){
                    c = null;
                }
            }
        }
        if (this.fixedTags){
            for (int j = 1; j <= this.nrTags; j++){
                if (this.fix.bases[j] < 0) continue;    // tag not fixed to some other
                if (this.finalRegisters[j] != null){
                }
                int dist = this.fix.dists[j];
                int[] base = this.finalRegisters[this.fix.bases[j]];
                if (dist == 0){
                    this.finalRegisters[j] = base;
                } else {
                    this.finalRegisters[j] = new int[base.length];
                    int[] cur = this.finalRegisters[j];
                    for (int k = 0; k < base.length; k++){
                        cur[k] = base[k];
                        if (base[k] >= 0) cur[k] += dist;
                    }
                }
            }
        }
    }

    private void computeHistories(int fc, String text, boolean tdfa){
        // another representation is with an array that contains lists of histories: working
        // backwards I could allocate a list element each time an offset is added and make it
        // point to from a directory; all other offsets are prepended

        if (this.finalRegisters == null || this.finalRegisters.length < this.nrTags+1){
            if (this.finalRegisters != null){
            }
            this.finalRegisters = new int[this.nrTags+1][];
        }
        // compute the length of each history
        int[] lengths = new int[this.nrTags+1];
        int i = text.length();
        for (int c = fc; c >= 0;){
            int piece = this.confPiece[c];
            int ln = this.confTstrings[piece];
            for (int j = ln-1; j >= 0; j--){
                int p = this.confTstrings[piece+j+1];
                int t = (p >= T_NTAG) ? (p - T_NTAG) : (p - T_TAG);
                lengths[t]++;                    
            }
            if (i == 0) break;
            int bas = this.confLinks.base[c];
            int start = bas+this.statesSeq[--i];
            int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
            c = ele;
        }
        // allocate then each history
        for (int j = 1; j < lengths.length; j++){
            if (this.finalRegisters[j] != null){
            }
            this.finalRegisters[j] = new int[lengths[j]];
        }
        // fill then each history
        i = text.length();
        for (int c = fc; c >= 0;){
            int piece = this.confPiece[c];
            int ln = this.confTstrings[piece];
            for (int j = ln-1; j >= 0; j--){
                int p = this.confTstrings[piece+j+1];
                if (p >= T_NTAG){
                    int t = p - T_NTAG;
                    this.finalRegisters[t][--lengths[t]] = -1;
                } else {
                    int t = p - T_TAG;
                    this.finalRegisters[t][--lengths[t]] = i;
                }
            }
            if (i == 0) break;
            int bas = this.confLinks.base[c];
            int start = bas+this.statesSeq[--i];
            int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
            c = ele;
        }
        if (this.fixedTags){
            for (int j = 1; j <= this.nrTags; j++){
                if (this.fix.bases[j] < 0) continue;    // tag not fixed to some other
                if (this.finalRegisters[j] != null){
                }
                int dist = this.fix.dists[j];
                int[] base = this.finalRegisters[this.fix.bases[j]];
                if (dist == 0){
                    this.finalRegisters[j] = base;
                } else {
                    this.finalRegisters[j] = new int[base.length];
                    int[] cur = this.finalRegisters[j];
                    for (int k = 0; k < base.length; k++){
                        cur[k] = base[k];
                        if (base[k] >= 0) cur[k] += dist;
                    }
                }
            }
        }
    }

    /**
     * Compute the histories (aka final registers) from the final tstring.
     */

    private void computeHistoriesTstring(){
        if (this.finalRegisters == null || this.finalRegisters.length < this.nrTags+1){
            if (this.finalRegisters != null){
            }
            if (this.offsets){
                this.finalRegisters = new int[this.nrTags/2+1][];
            } else {
                this.finalRegisters = new int[this.nrTags+1][];
            }
        }
        // compute the length of each history
        int[] lengths = new int[this.offsets ? this.nrTags/2+1 : this.nrTags+1];
        if (this.offsets){
            for (int i = 0; i < lengths.length; i++){
                lengths[i] = 2;
            }
        } else {
            for (int i = 0; i < this.treeLen; i++){
                int t = 0;
                char c = this.treearr[i];
                if (c >= T_TAG){
                    t = charToTag(c);
                }
                if (t == 0) continue;
                if (t < 0) t = -t;
                if (this.subhist){
                    if (t % 2 == 1 && i > 0){
                        AstNode ast = this.astMap[this.tagAst[t]];
                        if (ast.fat != null && ast.fat.kind == A_GRO){
                            c = this.treearr[i-1];
                            if (c >= T_TAG){
                                int r = charToTag(c);
                                if (r < 0) r = -r;
                                AstNode enc = ast.fat;
                                if (enc != null && r == otag(enc)){
                                    if (lengths[t] > 0){
                                        lengths[t]++;
                                    }
                                }
                            }
                        }
                    }
                }
                lengths[t]++;                    
            }
        }
        // allocate then each history
        for (int j = 0; j < lengths.length; j++){
            if (!this.offsets && j == 0) continue;
            if (this.finalRegisters[j] != null){
            }
            this.finalRegisters[j] = new int[lengths[j]];
        }
        Arrays.fill(lengths,0);
        // fill then each history
        int offs = 0;
        for (int i = 0; i < this.treeLen; i++){
            int t = 0;
            char c = this.treearr[i];
            if (c >= T_TAG){
                t = charToTag(c);
            } else {
                offs++;
            }
            if (t == 0) continue;
            if (this.subhist){
                int tt = t > 0 ? t : -t;
                if (tt % 2 == 1 && i > 0){
                    AstNode ast = this.astMap[this.tagAst[tt]];
                    if (ast.fat != null && ast.fat.kind == A_GRO){
                        c = this.treearr[i-1];
                        if (c >= T_TAG){
                            int r = charToTag(c);
                            if (r < 0) r = -r;
                            AstNode enc = ast.fat;
                            if (enc != null && r == otag(enc)){
                                if (lengths[tt] > 0){
                                    this.finalRegisters[tt][lengths[tt]++] = -2;
                                }
                            }
                        }
                    }
                }
            }
            if (this.offsets){
                int p = offs;
                if (t < 0){
                    p = -1;
                    t = -t;
                }
                if (t % 2 == 0){
                    this.finalRegisters[t/2-1][1] = p;
                } else {
                    this.finalRegisters[(t-1)/2][0] = p;
                }
            } else {
                if (t < 0){
                    t = -t;
                    this.finalRegisters[t][lengths[t]++] = -1;
                } else {
                    this.finalRegisters[t][lengths[t]++] = offs;
                }
            }
        }
        if (this.fixedTags && !this.useTnfa){
            buildFixedTags();
        }
    }

    /*
     * A navigable tree could have this form:
     *
     *      - a sequence of nodes, each represented as a piece of an array:
     *
     *          - link to next sibling
     *          - number of alternative
     *          - start offset
     *          - end offset
     *          - link to first son
     *          - link to father
     *
     *      - the name, if named group could be kept in ASTs
     *      - perhaps, sequences of input characters could be represented with only a single node
     *        (which occurs when a node is a concatenation and has only terminal sons)
     *      - link 0 denotes null, index 0 is reserved
     *
     * This can be build in the backward pass.
     *
     * Navigation in a DOM is done having the reference of a node and accessing these properties
     * of the node (the reference of a node can be got takind the root, or getting it with
     * methods that seek the node using its name, id, etc.):
     *
     *   - parentNode
     *   - childNodes
     *   - firstChild
     *   - lastChild
     *   - nextSibling
     *   - previousSibling
     *
     * I could provide a method that delivers an object containing these fields.
     * If the tree would be represented usind objects, then it would be possible to access
     * it much the same as it is done in javascript, e.g. root.childNodes[2].firstChild....
     * but this requires much memory. Since the tree is stored in compact form, there is
     * a need to call a method to get the nodes in object form. E.g.
     *
     *     ReTdfa.DOM root = r.domRoot();
     *     ReTdfa.DOM node = r.dom(root.childNodes[2]);
     *     node = r.dom(node.firstChild);
     *     ...
     */

    /** The offset of the brother field in tree nodes. */
    private static final int N_BRO = 0;

    /** The offset of the alt field in tree nodes. */
    private static final int N_ALT = 1;

    /** The offset of the start field in tree nodes. */
    private static final int N_START = 2;

    /** The offset of the end field in tree nodes. */
    private static final int N_END = 3;

    /** The offset of the son field in tree nodes. */
    private static final int N_SON = 4;

    /** The offset of the father field in tree nodes. */
    private static final int N_FAT = 5;

    /** The offset of the type field in tree nodes. */
    private static final int N_TYPE = 6;

    /** The number of fields in tree nodes. */
    private static final int N_FIELDS = 7;

    /**
     * Deliver a string representing the specified tree node.
     *
     * @param      i index of the node
     */

    private String treeNodeToString(int i){
        return String.format("%s: node bro: %s, ALT: %s, start: %s, end: %s, son: %s, fat: %s, type: %s",
            i,this.tree[i+N_BRO],this.tree[i+N_ALT],
            this.tree[i+N_START],
            this.tree[i+N_END],this.tree[i+N_SON],this.tree[i+N_FAT],this.tree[i+N_TYPE]);
    }

    /**
     * Trace the tree.
     */

    private void traceTree(){
        for (int i = 1; i < this.treeLength; i += N_FIELDS){
            Trc.out.printf("%s\n",treeNodeToString(i));
        }
    }

    /**
     * Append to the specified string builder a string representing the tree.
     *
     * @param      sb string builder
     * @param      n index of the root
     * @param      text string matched
     */

    private String treeToString(String text){
        StringBuilder sb = new StringBuilder();
        sb.append("(");
        treeToString(sb,1,text);
        sb.append(")");
        return sb.toString();
    }
    private void treeToString(StringBuilder sb, int n, String text){
/*
        sb.append("(");
        for (int i = this.tree[n+N_SON]; i != 0; i = this.tree[i+N_BRO]){
            if (this.tree[i+N_SON] == 0){
                sb.append(text.charAt(this.tree[i+N_START]));
            } else {
                treeToString(sb,i,text);
            }
        }
        sb.append(")");
*/
        switch (this.tree[n+N_TYPE]){
        case DOM.T_LEAF:
            sb.append(this.text.substring(this.tree[n+N_START],this.tree[n+N_END]));
            break;
        case DOM.T_EMPTY:
            sb.append("()");
            break;
        default:
            sb.append("(");
            for (int i = this.tree[n+N_SON]; i != 0; i = this.tree[i+N_BRO]){
                treeToString(sb,i,text);
            }
            sb.append(")");
        }
    }

    /**
     * Append to the specified string builder a string representing the LST of the tree.
     *
     * @param      sb string builder
     * @param      n index of the root
     * @param      text string matched
     */

/*
    private void treeToLst(StringBuilder sb, int n, String text){
        AstNode ast = this.astMap[this.tree[n+N_AST]];
        sb.append("(");
        sb.append(posToString(ast.pos));
        if (ast.kind == A_LEA){
            sb.append(text.charAt(this.tree[n+N_START]));
            sb.append(posToString(ast.pos));
        } else {
            for (int i = this.tree[n+N_SON]; i != 0; i = this.tree[i+N_BRO]){
                treeToLst(sb,i,text);
            }
        }
        sb.append(")");
        sb.append(posToString(this.astMap[this.tree[n+N_AST]].pos));
        if (n == 1) sb.append("⊣$");
    }
*/

    /** The tree. */
    private int[] tree;

    /** The length of the tree. */
    private int treeLength;

    /**
     * Build the tree visiting backwards the chain of configurations starting from the
     * specified final one.
     *
     * @param      fc final configuration
     * @param      text string matched
     */

    private void buildTree(Config fc, String text){
        this.treeLength = 1;
        if (this.tree == null){
            this.tree = new int[1000];
        }
        int i = text.length();
        int curnode = 0;
        for (Config c = fc; c != null;){
            int t = 0;
            int piecelen = 0;
            if (this.xcomp){
                piecelen = c.x.length()-1;
            } else {
                piecelen = c.path.length-1;
            }
            for (int j = piecelen; j >= 0; j--){
                int p = 0;
                if (this.xcomp){
                    p = c.x.charAt(j);
                } else {
                    p = c.path[j];
                }
                if (p >= T_TAG){
                    t = charToTag((char)p);
                    // negative tags are useless here: the tree is determined by the
                    // positive ones; the negative ones can only tell which alternative a son is
                    // when a node has several in the RE
                    if (t < 0) continue;
                    if (t % 2 == 1){                      // opening tag
                        // find its node, n
                        this.tree[curnode+N_START] = i;   // start
                        if (curnode != 0){
                            curnode = this.tree[curnode+N_FAT];
                        }
                    } else {                              // closing tag
                        if (this.tree == null || this.tree.length-this.treeLength < N_FIELDS){
                            if (this.tree != null){
                                this.tree = Arrays.copyOf(this.tree,this.treeLength+1000);
                            } else {
                                this.tree = new int[1000];
                            }
                            //Trc.out.printf("tree %s\n",this.tree.length * 4 + 4);
                        }
                        int n = this.treeLength;
                        this.tree[n+N_BRO] = 0;
                        int astnr = this.tagAst[t];
                        this.tree[n+N_ALT] = this.tagAltTable[t];
                        this.tree[n+N_TYPE] = this.tagKindTable[t];
                        this.tree[n+N_START] = 0;
                        this.tree[n+N_END] = i;
                        this.tree[n+N_SON] = 0;
                        this.tree[n+N_FAT] = 0;
                        this.treeLength += N_FIELDS;
                        if (curnode != 0){
                            this.tree[n+N_BRO] = this.tree[curnode+N_SON];
                            this.tree[curnode+N_SON] = n;
                            this.tree[n+N_FAT] = curnode;
                        }
                        curnode = n;
                    }
                } else {
                    --i;
                }
            }
            if (i == 0) break;
            if (this.useTnfa){
                --i;
                if (c.orig == null) break;
                c = c.orig.get(0);
                if (c != null){
                    c = c.orig.get(0);
                }
            } else {
                int bas = this.confLinks.base[c.id];
                int start = bas+this.statesSeq[--i];
                int ele = this.confLinks.mergetable[start];
                c = this.confTable[ele];
            }
        }
    }


    private void buildTree(int fc, String text){
        this.treeLength = 1;
        if (this.tree == null){
            this.tree = new int[1000];
        }
        int i = text.length();
        int curnode = 0;
        for (int c = fc; c >= 0;){
            int t = 0;
            int piece = this.confPiece[c];
            int piecelen = this.confTstrings[piece];
            for (int j = piecelen; j >= 0; j--){
                int p = this.confTstrings[piece+j];
                if (p >= T_TAG){
                    t = charToTag((char)p);
                    // negative tags are useless here: the tree is determined by the
                    // positive ones; the negative ones can only tell which alternative a son is
                    // when a node has several in the RE
                    if (t < 0) continue;
                    if (t % 2 == 1){                      // opening tag
                        // find its node, n
                        this.tree[curnode+N_START] = i;   // start
                        if (curnode != 0){
                            curnode = this.tree[curnode+N_FAT];
                        }
                    } else {                              // closing tag
                        if (this.tree == null || this.tree.length-this.treeLength < N_FIELDS){
                            if (this.tree != null){
                                this.tree = Arrays.copyOf(this.tree,this.treeLength+1000);
                            } else {
                                this.tree = new int[1000];
                            }
                            //Trc.out.printf("tree %s\n",this.tree.length * 4 + 4);
                        }
                        int n = this.treeLength;
                        this.tree[n+N_BRO] = 0;
                        int astnr = this.tagAst[t];
                        this.tree[n+N_ALT] = this.tagAltTable[t];
                        this.tree[n+N_TYPE] = this.tagKindTable[t];
                        this.tree[n+N_START] = 0;
                        this.tree[n+N_END] = i;
                        this.tree[n+N_SON] = 0;
                        this.tree[n+N_FAT] = 0;
                        this.treeLength += N_FIELDS;
                        if (curnode != 0){
                            this.tree[n+N_BRO] = this.tree[curnode+N_SON];
                            this.tree[curnode+N_SON] = n;
                            this.tree[n+N_FAT] = curnode;
                        }
                        curnode = n;
                    }
                }
            }
            if (i == 0) break;
            int bas = this.confLinks.base[c];
            int start = bas+this.statesSeq[--i];
            int ele = this.confLinks.mergetable[start];
            c = ele;
        }
    }

    private void buildTreeTrie(int fc, String text){
        this.treeLength = 1;
        if (this.tree == null){
            this.tree = new int[1000];
        }
        int i = text.length();
        int curnode = 0;
        for (int c = fc; c != 0;){
            int blknr = c >> 16;
            int blkoff = c & 0xffff;
            char[] blk = this.tstrie.dir[blknr];
            int piecelen = blk[blkoff+2];
            int t = 0;
            for (int j = blkoff+2+piecelen; j >= blkoff+3; j--){
                int p = blk[j];
                if (p >= T_TAG){
                    t = charToTag((char)p);
                    // negative tags are useless here: the tree is determined by the
                    // positive ones; the negative ones can only tell which alternative a son is
                    // when a node has several in the RE
                    if (t < 0) continue;
                    if (t % 2 == 1){                      // opening tag
                        // find its node, n
                        this.tree[curnode+N_START] = i;   // start
                        if (curnode != 0){
                            curnode = this.tree[curnode+N_FAT];
                        }
                    } else {                              // closing tag
                        if (this.tree == null || this.tree.length-this.treeLength < N_FIELDS){
                            if (this.tree != null){
                                this.tree = Arrays.copyOf(this.tree,this.treeLength+1000);
                            } else {
                                this.tree = new int[1000];
                            }
                            //Trc.out.printf("tree %s\n",this.tree.length * 4 + 4);
                        }
                        int n = this.treeLength;
                        this.tree[n+N_BRO] = 0;
                        int astnr = this.tagAst[t];
                        this.tree[n+N_ALT] = -1;
                        if (this.astMap[astnr].fat != null &&
                            this.astMap[astnr].fat.kind == A_ALT){
                            this.tree[n+N_ALT] = this.astMap[astnr].altnr;
                        }
                        this.tree[n+N_TYPE] = astKindToDomType(this.astMap[astnr]);
                        this.tree[n+N_START] = 0;
                        this.tree[n+N_END] = i;
                        this.tree[n+N_SON] = 0;
                        this.tree[n+N_FAT] = 0;
                        this.treeLength += N_FIELDS;
                        if (curnode != 0){
                            this.tree[n+N_BRO] = this.tree[curnode+N_SON];
                            this.tree[curnode+N_SON] = n;
                            this.tree[n+N_FAT] = curnode;
                        }
                        curnode = n;
                    }
                } else {
                    i--;
                }
            }
            if (i == 0) break;
            c = blk[blkoff] << 16 | blk[blkoff+1];
        }
    }


    public class DOM {
        int id;
        int parentNode;
        int[] childNodes;
        int firstChild;
        int lastChild;
        int nextSibling;
        int previousSibling;
        int start;
        int end;
        int altNumber;
        int nodeType;                  // 0..5: same as AST kind, 6..10 same as AST groupKind
        public static final int T_LEAF  = A_LEA;
        public static final int T_ALT   = A_ALT;
        public static final int T_CONC  = A_CON;
        public static final int T_EMPTY = A_EMP;
//        public static final int T_NULL  = A_NUL;
        public static final int T_GROUP = G_GRO + 6;
        public static final int T_OPT   = G_OPT + 6;
        public static final int T_STAR  = G_RE0 + 6;
        public static final int T_PLUS  = G_RE1 + 6;
        public static final int T_INTER = G_RE2 + 6;
        public String toString(){
            StringBuffer sb = new StringBuffer();
            sb.append(this.id);
            sb.append(" type: ");
            //sb.append(this.nodeType);
            String type = "";
            switch (this.nodeType){
            case T_LEAF: type = "T_LEAF"; break;
            case T_ALT: type = "T_ALT"; break;
            case T_CONC: type = "T_CONC"; break;
            case T_EMPTY: type = "T_EMPTY"; break;
            case T_GROUP: type = "T_GROUP"; break;
            case T_OPT: type = "T_OPT"; break;
            case T_STAR: type = "T_STAR"; break;
            case T_PLUS: type = "T_PLUS"; break;
            case T_INTER: type = "T_INTER"; break;
            }
            sb.append(type);
            sb.append(":  ^");
            sb.append(this.parentNode);
            if (this.firstChild != 0){
                sb.append(" children ");
                sb.append(this.firstChild);
                sb.append("..");
                sb.append(this.lastChild);
            }
            if (this.previousSibling != 0){
                sb.append(" <");
                sb.append(this.previousSibling);
            }
            if (this.nextSibling != 0){
                sb.append(" >");
                sb.append(this.nextSibling);
            }
            if (this.childNodes != null){
                sb.append(" ");
                sb.append(Arrays.toString(this.childNodes));
            }
            sb.append(" off: ");
            sb.append(this.start);
            sb.append(":");
            sb.append(this.end);
            sb.append(" |");
            sb.append(text.substring(this.start,this.end));
            sb.append("|");
            if (this.altNumber >= 0){
                sb.append(" altNr: ");
                sb.append(this.altNumber);
            }
            return sb.toString();
        }
    }

    public DOM domRoot(){
        return dom(1);
    }
    public DOM dom(int node){
        DOM res = new DOM();
        res.id = node;
        res.parentNode = this.tree[node+N_FAT];
        int n = 0;
        for (int i = this.tree[node+N_SON]; i != 0; i = this.tree[i+N_BRO]){
            n++;
        }
        res.childNodes = null;
        if (n > 0) res.childNodes = new int[n];
        n = 0;
        for (int i = this.tree[node+N_SON]; i != 0; i = this.tree[i+N_BRO]){
            res.childNodes[n++] = i;
        }
        res.firstChild = 0;
        res.lastChild = 0;
        if (res.childNodes != null){
            res.firstChild = res.childNodes[0];
            res.lastChild = res.childNodes[n-1];
        }
        res.previousSibling = 0;
        res.nextSibling = 0;
        if (res.parentNode != 0){
            for (int i = this.tree[res.parentNode+N_SON]; i != 0; i = this.tree[i+N_BRO]){
                if (i == node){
                    res.nextSibling = this.tree[i+N_BRO];
                    break;
                }
                res.previousSibling = i;
            }
        }
        res.start = this.tree[node+N_START];
        res.end = this.tree[node+N_END];
        res.altNumber = this.tree[node+N_ALT];
        res.nodeType = this.tree[node+N_TYPE];
        return res;
    }

    private void traceDOM(){
        traceDOM(1,0);
    }
    private void traceDOM(int n, int lev){
        DOM d = dom(n);
        Trc.out.printf("%s%s\n",indent(lev),d);
        if (d.childNodes != null){
            for (int i = 0; i < d.childNodes.length; i++){
                traceDOM(d.childNodes[i],lev+1);
            }
        }
    }

    /** A growable array string that computes also the memory used. */

    class CharVector {

        /** The container. */
        char[] arr;

        /** The elements in it. */
        int length;

        /** The number of elements added when enlarging. */
        private static final int QUANTUM = 100;

        /**
         * Construct an empty vector.
         */

        CharVector(){
            this.arr = new char[QUANTUM];
            this.length = 0;
        }

        /**
         * Construct an empty vector with the specified contents.
         *
         * @param      v other vector to copy
         */

        CharVector(CharVector v){
            this.arr = Arrays.copyOf(v.arr,v.arr.length);
            this.length = v.length;
        }

        /**
         * Remove all the elements contained in this vector, if any.
         */

        void clear(){
            this.length = 0;
        }

        /**
         * Enlarge the container ensuring that there is at least the specified space.
         *
         * @param      len space
         */

        void enlarge(int len){
            int newlen = this.arr.length + QUANTUM;
            if (this.arr.length - this.length < len){   // still not enough
                newlen += len - (this.arr.length - this.length);
            }
            if (newlen >= 1000){
                newlen *= 1.5;
            }
            this.arr = Arrays.copyOf(this.arr,newlen);
        }

        /**
         * Append all the values of the specified array at the end of the current one.
         *
         * @param      v array
         */

        void append(char[] v){
            if (v == null) return;
            if (this.arr.length - this.length < v.length){
                enlarge(v.length);
            }
            System.arraycopy(v,0,this.arr,this.length,v.length);
            this.length += v.length;
        }

        /**
         * Append the contents of the specified vector at the end of the current one.
         *
         * @param      v vector
         */

        void append(CharVector v){
            if (v == null) return;
            if (this.arr.length - this.length < v.length){
                enlarge(v.length);
            }
            System.arraycopy(v.arr,0,this.arr,this.length,v.length);
            this.length += v.length;
        }

        /**
         * Append the contents of the specified Tstring at the end of the current one.
         *
         * @param      t Tstring
         */

        void append(Tstring t){
            if (t == null) return;
            int len = t.length();
            if (this.arr.length - this.length < len){
                enlarge(len);
            }
            for (int i = 0, j = this.length; i < len; i++,j++){
                this.arr[j] = t.charAt(i);
            }
            this.length += len;
        }

        /**
         * Append the specified element at the end of the current object.
         *
         * @param      c char
         */

        void add(char c){
            if (this.arr.length - this.length < 1){
                enlarge(1);
            }
            this.arr[this.length++] = c;
        }

        /**
         * Deliver a Tstring with the contents of this object
         *
         * @return     Tstring
         */

        Tstring toTstring(){
            return new Tstring(this.arr,this.length );
        }
    }

    /**
     * Parse the specified string against this RE without using tags and collecting the
     * final Tstring or tag histories in a single pass.
     *
     * @param      text string
     * @return     <code>true</code> if successful, and <code>false</code> otherwise
     */

    /* There are two cases to consider:
     *
     *  1. a state can refer to itself, and thus have configs that have other configs in
     *     the same state as predecessors. Ideally, we should have a config array in
     *     each state visited, and when taking the previous Tstrings, access it and then update
     *     the current one, otherwise we mix partial results of the current one with old values.
     *     The solution is to use two arrays of configs, one olding the partial Tstrings of
     *     the previous step, and another for the current step.
     *     Each element is an array in which the partial Tstring associated to the precedessor
     *     configurations are copied and the path segment of the current ones appended.
     *  2. two or several configurations in a state can have a same predecessor one.
     *     Only the last one can reuse the previous array; all the others must use a copy of it,
     *     or just use their own concatenating properly the pieces. There is a need to mark the
     *     configs that have several successors, and then to flag the ones that are followed by
     *     others that in some previous state refer to the same marked configs: take a config: if
     *     it has a marked predecessor (no matter what the state is), then if followed by any other
     *     config that has the same predecessor, then flag it.
     * All this, however, does not eliminate cloning, it can only reduce it at the cost of some
     * involved calculations. Therefore, it is pointless to achieve it.
     * At the end it takes the array of the final config.
     * However, there would be quite a lot of copying, so could be organized as a trie:
     * at each step it would make the array point to list elements that have a pointer to the two
     * pieces to collect. The elements could be kept in an array (much the same as Earley) items.
     * But this would require another pass, so it would be pretty the same as the two passes
     * solution (possibly worse). So, the only possibility is to keep an array of arrays and
     * grow them.
     * Collecting histories is even more complex because each path has its own, and they should
     * have the same treatment as path segments.
     */

    public boolean matchTagless1pass(String text){
        TDFAStateTable dfa = this.tdfa;
        if (!this.transtable){
            System.out.printf("matchTagless1pass requires transtable\n");
            return false;
        }
        if (this.partialPaths == null || this.partialPaths.length < this.confSeq){
            if (this.partialPaths != null){
                this.partialPaths = Arrays.copyOf(this.partialPaths,this.confSeq);
                this.partialPathsOld = Arrays.copyOf(this.partialPathsOld,this.confSeq);
            } else {
                this.partialPaths = new CharVector[this.confSeq];
                this.partialPathsOld = new CharVector[this.confSeq];
            }
        }
        for (int i = 0; i < this.partialPaths.length; i++){
            if (this.partialPaths[i] != null){
                this.partialPaths[i].clear();
            }
            if (this.partialPathsOld[i] != null){
                this.partialPathsOld[i].clear();
            }
        }

        TDFAstate prevState = null;
        TDFAstate state = dfa.head;               // initial state
        boolean res = true;
        int i = 0;
        for (; i < text.length(); i++){
            if (text.charAt(i) >= 128){
                this.error = true;
                res = false;
                break;
            }
            for (Config c : state.set){
                if (this.partialPaths[c.id] == null){
                    this.partialPaths[c.id] = new CharVector();
                }
                if (prevState != null){
                    int bas = this.confLinks.base[c.id];
                    int start = bas+prevState.number;
                    int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
                    this.partialPaths[c.id].clear();
                    this.partialPaths[c.id].append(this.partialPathsOld[ele]);
                    if (this.xcomp){
                        this.partialPaths[c.id].append(c.x);
                    } else {
                        if (this.finreg){
                            this.partialPaths[c.id].append(c.x);
                        } else {
                            this.partialPaths[c.id].append(c.path);
                        }
                    }
                } else {
                    if (this.xcomp){
                        this.partialPaths[c.id].append(c.x);
                    } else {
                        if (this.finreg){
                            this.partialPaths[c.id].append(c.x);
                        } else {
                            this.partialPaths[c.id].append(c.path);
                        }
                    }
                }
                if (this.xcomp){
                } else {
                }
                this.partialPaths[c.id].add(text.charAt(i));
            }
            CharVector[] tmp = this.partialPaths;           // swap
            this.partialPaths = this.partialPathsOld;
            this.partialPathsOld = tmp;

            TDFAarc arc = null;
            int base = dfa.transTable.base[state.number];
            int sym = classMap[text.charAt(i)];
            int nextarc = dfa.transTable.check[base+sym] == base ?
                dfa.transTable.mergetable[base+sym] : dfa.transTable.holeValue;
            if (nextarc < 0){
                this.error = true;
                res = false;
                break;
            }
            arc = dfa.arcsTable[nextarc];
            prevState = state;
            state = arc.nextState;
        }
        fin: if (i == text.length()){            // all text eaten
            if (!state.isFinal){
                this.error = true;
                res = false;
                break fin;
            }
            for (Config c : state.set){
                if (c.q.isFinal){
                    if (this.partialPaths[c.id] == null){
                        this.partialPaths[c.id] = new CharVector();
                    }
                    if (prevState != null){
                        int bas = this.confLinks.base[c.id];
                        int start = bas+prevState.number;
                        int ele = this.confLinks.check[start] == bas ? this.confLinks.mergetable[start] : -1;
                        this.partialPaths[c.id].clear();
                        this.partialPaths[c.id].append(this.partialPathsOld[ele]);
                        if (this.xcomp){
                            this.partialPaths[c.id].append(c.x);
                        } else {
                            if (this.finreg){
                                this.partialPaths[c.id].append(c.x);
                            } else {
                                this.partialPaths[c.id].append(c.path);
                            }
                        }
                    } else {
                        if (this.xcomp){
                            this.partialPaths[c.id].append(c.x);
                        } else {
                            if (this.finreg){
                                this.partialPaths[c.id].append(c.x);
                            } else {
                                this.partialPaths[c.id].append(c.path);
                            }
                        }
                    }
                    break;
                }
            }
        } else {
            this.error = true;
            res = false;
        }
        if (res && (this.matchTstring || this.finreg || this.parsetree)){
            // find the final config
            Config fc = null;
            for (Config c : state.set){
                if (c.q.isFinal){
                    if (fc != null){
                        System.out.printf("!! several final configs\n");
                    }
                    fc = c;
                }
            }
            if (this.matchTstring || this.finreg){
                // copy the final tstring in treearr, do not make it point to the partialpath
                // because it would impair reuse
                int len = this.partialPaths[fc.id].length;
                if (this.treearr == null || this.treearr.length < len){
                    if (this.treearr != null){
                    }
                    this.treearr = new char[len];
                }
                this.treeLen = len;
                System.arraycopy(this.partialPaths[fc.id].arr,0,this.treearr,0,len);
            }
            if (this.finreg){
                computeHistoriesTstring();
                if (!this.matchTstring) this.treeLen = 0;
            }
            if (this.parsetree){
                buildTree(fc,text);
            }
        }
        return res;
    }

    /** The array of partial paths. */
    private CharVector[] partialPaths;

    /** The array of partial paths of the previous step. */
    private CharVector[] partialPathsOld;


    // ---------- Optimized compilation -----------------
    /** Histories. */

    class History {

        /** The directory. */
        IntVector[] h;

        /** The number of them. */
        int length;

        /**
         * Deliver a string representing the histories.
         *
         * @return  string
         */

        public String toString(){
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < this.length; i++){
                if (i > 0) sb.append(",");
                sb.append(subHistoryToString(this.h[i]));
            }
            return sb.toString();
        }

        /**
         * Ensure that there exist the specified history.
         *
         * @param   n number of the history
         */

        public void ensure(int n){
            this.length = n + 1;
            if (this.h == null){
                int len = 10;
                if (n > 0) len = this.length;
                this.h = new IntVector[len];
            } else if (this.length >= this.h.length){
                this.h = Arrays.copyOf(this.h,this.length+10);
            }
            if (this.h[n] == null){
                this.h[n] = new IntVector();
            }
        }

        /**
         * Clear the histories.
         */

        public void clear(){
            if (this.h != null){
                for (int i = 0; i < this.h.length; i++){
                    if (this.h[i] != null) this.h[i].clear();
                }
            }
            this.length = 0;
        }
    }

    /** A reusable history object. */
    private History hist1;

    /** A reusable history object. */
    private History hist2;

    /**
     * Fill the history object with the ones of the specified tag in the specified path.
     *
     * @param      a last arc of the path
     * @param      t tag
     * @param      arcs
     * @param      prev 
     */

    /* Instead of a Tstring here we visit the chain of arcs, and at the end add the ordinal
     * of the ending configuration.
     * To distinguish between arcs and ending configuration, the arcs are represented with
     * positive integers and configurations with negative integers.
     * Since the configurations table does not exist at this point, I use the sequence numbers
     * of the input configurations in the reached list.
     * N.B. the histories are computed backwards, thus I compare them backwards in subhistory.
     * The paths are represented with an array of pairs tag,prev. In result the index of the
     * paths in this array.
     * There is no need to apply it to the arcs containing input symbols because they have
     * no tags, so the history is empty.
     *
     *       2:      (tag)
     *               -reached nr
     *               ....
     *               (tag) <-.
     *               (link)  |
     *       z  -->  tag     |
     *               link ---'
     *
     * If precedessors can be used, a new representation for paths is used: result contains
     * the number of the predecessor state (actually, the number +1 because 0 means null, and
     * 0 is a legal state number; it can also contain -n where n is the number of the reached
     * starting configuration + 1); pathTag contains the tag tha is on the arc from a state
     * and its prececessor, i.e. n and result[n]-1.
     * This allows to use only one array, pathTag instead of creating paths in an array (which
     * are created each time paths are visited).
     */

    /** A reusable array containing several paths. */
    private int[] paths;

    /** The index in it. */
    private int pathsi;

    /** A reusable path. */
    private int[] path1;

    /** A reusable path. */
    private int[] path2;

    /**
     * Deliver a string representing the specified path.
     *
     * @param      p path
     * @param      n length of the significant part of it
     * @return     string
     */

    private String pToString(int[] p, int n){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++){
            if (sb.length() > 0) sb.append(" ");
            sb.append(p[i]);
        }
        return sb.toString();
    }

    /**
     * Deliver the e-history of the specified path for the specified tag.
     *
     * @param      a path
     * @param      n length of the significant part of it
     * @param      t tag
     * @param      hist returned history
     * @param      o first element of history
     */

    private void e_history(int[] a, int n, int t, History hist, int o){
        int i = 0;
        int j = 0;
        hist.clear();
        hist.ensure(0);
        hist.h[0].add(o);
        for (;;){
            l: for (; i < n; i++){
                int tag = a[i];
                if (tag == 0) continue;
                // for (int u = 0; u < 2*Math.ceil(t/2.0)-1; u++){
                //    if (tag == u || tag == -u) break l;
                // }

                int atag = tag > 0 ? tag : -tag;
                if (atag < 2*Math.ceil(t/2.0)-1) break;

                if (tag == t) hist.h[j].add(INFINITE);
                if (tag == -t) hist.h[j].add(-1);       // -1 = phi
            }
            if (i >= n) break;
            j++;
            hist.ensure(j);
            for (; i < n; i++){
                int tag = a[i];
                if (tag == 0) continue;
                if (tag == t || tag == -t) break;
            }
        }
    }

    /**
     * Deliver a string representing the specified paths.
     *
     * @param      a first element, shown at the beginning
     * @param      paths path
     * @return     string
     */

    private String pathToString(int a, int[] paths){
        StringBuilder sb = new StringBuilder();
        for (;;){
            if (sb.length() > 0) sb.append(" ");
            sb.append(a);
            sb.append(":");
            sb.append(paths[a++]);
            sb.append(",");
            sb.append(paths[a]);
            a = paths[a];
            if (a < 0) break;
        }
        return sb.toString();
    }

    /**
     * Deliver a string representing the specified paths.
     *
     * @param      a first element, shown at the beginning
     * @param      paths paths
     * @return     string
     */

    private String pathToStr(int a, int[] paths){
        if (a < 0) return "(" + a + ")";
        StringBuilder sb = new StringBuilder();
        for (;;){
            if (sb.length() > 0) sb.insert(0," ");
            sb.insert(0,paths[a++]);
            a = paths[a];
            if (a < 0) break;
        }
        sb.append("(");
        sb.append(a);
        sb.append(")");
        return sb.toString();
    }

    /**
     * Tell if the firs paths is prior to the second one in the Posix ordering.
     *
     * @param      a1 index of the first path
     * @param      a2 index of the second path
     * @param      paths path array
     * @param      reached configurations from which the paths start
     * @param      fromState state from which the paths start
     * @return     <code>true</code> if it is, and <code>false</code> otherwise
     */

    private boolean lowerPOSIX(int a1, int a2, int[] paths, List<Config> reached, TDFAstate fromState)
        {
        int N = this.nrSubExpr;
        boolean res = false;

        int z = 0;
        int l1 = 0;
        if (a1 > 0){
            for (z = a1;; l1++){
                z = paths[z+1];
                if (z < 0) break;
            }
            l1++;
            if (this.path1 == null || this.path1.length < l1){
                this.path1 = new int[l1];
            }
            for (int l = l1-1;; l--){
                this.path1[l] = this.paths[a1++];
                a1 = paths[a1];
                if (a1 < 0) break;
            }
        }
        int l2 = 0;
        if (a2 > 0){
            for (z = a2;; l2++){
                z = paths[z+1];
                if (z < 0) break;
            }
            l2++;
            if (this.path2 == null || this.path2.length < l2){
                this.path2 = new int[l2];
            }
            for (int l = l2-1;; l--){
                this.path2[l] = this.paths[a2++];
                a2 = paths[a2];
                if (a2 < 0) break;
            }
        }
        Config o1 = reached.get(-a1-1);
        Config o2 = reached.get(-a2-1);
        if (this.okui){
            res = compare_posix(l1,l2,o1,o2,fromState) < 0;
            return res;
        } else if (!this.incremental && this.useTnfa){
            Tstring x = new Tstring();
            x.append(o1.x);
            for (int i = 0; i < l1; i++){
                x.append(this.path1[i]);
            }
            Tstring y = new Tstring();
            y.append(o2.x);
            for (int i = 0; i < l2; i++){
                y.append(this.path2[i]);
            }
            boolean resord = ordPosixSimpl(x,y);
            return resord;
        }
        if (2*N > this.nrTags) N = this.nrTags/2;
        if (this.hist1 == null) this.hist1 = new History();
        if (this.hist2 == null) this.hist2 = new History();

        l: for (int t = 1; t <= N; t++){
            e_history(this.path1,l1,2*t,this.hist1,o1.o[2*t]);
            e_history(this.path2,l2,2*t,this.hist2,o2.o[2*t]);
            int leng = Math.min(this.hist1.length,this.hist2.length);
            for (int i = 0; i < leng; i++){
                int cmp = subhistory(this.hist1.h[i],this.hist2.h[i]);
                if (cmp != 0){
                    res = cmp < 0;
                    break l;
                }
            }
        }
        return res;
    }

    /** A reusable closure result array. */
    private int[] result;

    /** A reusable closure topsort queue. */
    private TNFAstate[] topsort;

    /** A reusable closure newpass queue. */
    private TNFAstate[] newpass;

    /** A reusable closure status array. */
    private int[] status;

    /** A reusable closure visited array. */
    private boolean[] visited;

    /** A reusable closure character buffer. */
    private char[] charbuf;

    /** A reusable closure array of reached configurations. */
    private Config[] reachedConfigs;

    /** The status of a node that has not been processed. */
    private static int NOPASS = 0;

    /** The status of a node that has been processed in the main pass. */
    private static int TOPSORT = 1;

    /** The status of a node that has been processed in the second pass. */
    private static int NEWPASS = 2;

    /** The status of a node that has already been visited in the DFS visit. */
    private static int ACTIVE = 3;

    /** The strings representing the status of the nodes in topsort. */
    private static String[] stName = new String[]{"NOPASS","TOPSORT","NEWPASS","ACTIVE"};

    /** Whether the draft paper GOR1 is used: 0 = no, 1 = first draft, 2: second draft. */
//    private int paperGor1 = 2;
    private int paperGor1 = 0;

    /**
     * Deliver the configurations describing the paths to the states reached from the specified
     * ones with arcs labelled with tags or prios. The GOR1 algorithm is used.
     * Discard paths whose Tstrings are not prior for the Posix policy.
     *
     * @param      nfa reference to the state table
     * @param      reached start states
     * @param      configs reached states
     * @param      fromState starting state
     */

    private void closurep(TNFAStateTable nfa, List<Config> reached,
        List<Config> configs, final TDFAstate fromState){
        if (this.okui){
            this.paperGor1 = 2;
        }

        if (result == null || result.length < nfa.stateNr){
            result = new int[nfa.stateNr];
        } else {
            Arrays.fill(result,0);
        }
        if (reachedConfigs == null || reachedConfigs.length < reached.size()){
            reachedConfigs = new Config[reached.size()];
        }
        if (this.paths == null){
            this.paths = new int[100];
        }
        int nrea = 0;
        for (Config i : reached){
            reachedConfigs[nrea++] = i;
        }
        doit: {
            if (this.dfsClosure){
                if (closureDfs1(nfa,reached,result,paths))
                {
                    break doit;
                }
            }
            if (topsort == null || topsort.length < nfa.stateNr){
                topsort = new TNFAstate[nfa.stateNr];
            }
            if (newpass == null || newpass.length < nfa.stateNr){
                if (newpass != null){
                }
                newpass = new TNFAstate[nfa.stateNr];
                status = new int[nfa.stateNr];
            } else {
                Arrays.fill(status,0);
            }
            if (active == null || active.length < nfa.stateNr){
                active = new boolean[nfa.stateNr];
                next = new TNFAarc[nfa.stateNr];
            } else {
                Arrays.fill(active,false);
                Arrays.fill(next,null);
            }
            int sp = 0;
            TNFAstate[] linear = newpass;
            int LINEAR = NEWPASS;
            int np = 0;
            this.pathsi = 2;
            int nrconf = 0;
            // add start configurations

            if (paperGor1 == 1){
                Comparator<Config> comp = new Comparator<Config>(){
                    public int compare(Config c1, Config c2){
                        c1.y = c1.x;
                        if (c1.y == null) c1.y = new Tstring();
                        c2.y = c2.x;
                        if (c2.y == null) c2.y = new Tstring();
                        return lowerPOSIX(c1,c2,fromState) ? -1 : 0;
                    }};
                Collections.sort(reached,comp);
                nrea = 0;
                for (Config i : reached){
                    nrconf--;
                    if (result[i.q.number] == 0){
                        int iqnum = i.q.number;
                        result[iqnum] = nrconf;
                        linear[np++] = i.q;
                        next[iqnum] = i.q.transList;
                    }
                    reachedConfigs[nrea++] = i;
                }
                while (np > 0){
                    topsort[sp++] = linear[--np];
                }
            } else if (paperGor1 == 2){
                Comparator<Config> comp = new Comparator<Config>(){
                    public int compare(Config c1, Config c2){
                        int d = 0;
                        d = fromState.bmatrix[c1.order][c2.order] & 0x80000000;
                        return d < 0 ? 1 : -1;
                    }};
                Collections.sort(reached,comp);
                nrea = 0;
                for (Config i : reached){
                    nrconf--;
                    int iqnum = i.q.number;
                    result[iqnum] = nrconf;
                    next[iqnum] = i.q.transList;
                    reachedConfigs[nrea++] = i;
                    topsort[sp++] = i.q;
                }
            } else {
                for (Config i : reached){
                    nrconf--;
                    if (result[i.q.number] == 0 || lowerPOSIX(nrconf,result[i.q.number],paths,reached,fromState))
                        {
                        // lowerposix called here because when the RE is not fully tagged, then there can be
                        // two arcs labelled with the same input symbol that reach the same state
                        // With fully tagged REs it is never called
                        int iqnum = i.q.number;
                        result[iqnum] = nrconf;
                        status[iqnum] = TOPSORT;
                        topsort[sp++] = i.q;
                        next[iqnum] = i.q.transList;
                    }
                }
            }
            while (sp > 0){                              // while stack not empty
                // 1st pass: topological sorting
                while (sp > 0){                          // while stack not empty
                    TNFAstate q = topsort[--sp];         // pop
                    if (status[q.number] != LINEAR){
                        status[q.number] = TOPSORT;      // mark as visited
                        // find next admissible arc
                        TNFAstate p = null;
                        if (paperGor1 != 0){
                            for (;;){
                                p = explore(q,next,result,reached,fromState);
                                if (p == null){
                                    // done all depts visited
                                    status[q.number] = LINEAR;
                                    linear[np++] = q;
                                    break;
                                } else if (status[p.number] == NOPASS){
                                    // follow admissible arc
                                    topsort[sp++] = q;
                                    topsort[sp++] = p;
                                    next[p.number] = p.transList;
                                    break;
                                } else {
                                    active[p.number] = true;     // already visited
                                }
                            }
                        } else {
                            for (;;){
                                p = explore(q,next,result,reached,fromState);
                                if (p == null) break;
                                if (status[p.number] == NOPASS) break;
                                active[p.number] = true;     // already visited
                            }
                            if (p != null){
                                // follow admissible arc
                                topsort[sp++] = q;
                                topsort[sp++] = p;
                                next[p.number] = p.transList;
                            } else {
                                // done all depts visited
                                status[q.number] = LINEAR;
                                linear[np++] = q;
                            }
                        }
                    }
                }
                // 2nd pass: linear scan
                while (np > 0){
                    TNFAstate q = linear[--np];
                    int qnum = q.number;
                    if (active[qnum]){
                        // scan admissible arc
                        next[qnum] = q.transList;
                        for (;;){
                            TNFAstate p = explore(q,next,result,reached,fromState);
                            if (p == null) break;
                            int pnum = p.number;
                            if (status[pnum] == NOPASS){
                                topsort[sp++] = p;
                                next[pnum] = p.transList;
                            } else if (status[pnum] == LINEAR){
                                active[pnum] = true;
                            }
                        }
                    }
                    status[qnum] = NOPASS;
                    active[qnum] = false;
                }
            }
        } // doit

        configs.clear();
        for (int i = 0; i < nfa.stateNr; i++){
            int z = result[i];
            if (z == 0) continue;
            TNFAstate q = nfa.table[i];
            if (q.isCore){
                Tstring ts = new Tstring();
                int l1 = 0;
                int a = z;
                if (z > 0){
                    for (int zz = a;; l1++){
                        zz = this.paths[zz+1];
                        if (zz < 0) break;
                    }
                    l1++;
                }
                if (this.charbuf == null || this.charbuf.length < l1){
//                    if (this.useTnfa && this.charbuf != null){
//                    }
                    this.charbuf = new char[l1];
                }
                if (z > 0){
                    for (int l = l1-1;; l--){
                        this.charbuf[l] = intToTag(this.paths[a++]);
                        a = this.paths[a];
                        if (a < 0) break;
                    }
                }
                ts.append(this.charbuf,0,l1);

                Config conf = new Config(reachedConfigs[-a-1]);
                conf.q = q;
                conf.y = ts;
                configs.add(conf);
                if (!this.xcomp){
                    int len = 0;
                    for (int j = 0; j < conf.y.length(); j++){
                        int t = conf.y.getTag(j);
                        if (!this.tagless && !this.useTnfa){
                            if (this.finreg){
                                if (t >= 0 && this.fixedTags){
                                    if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                                }
                            } else {
                                if (t <= 0) continue;
                            }
                        } else {
                            if (t <= 0) continue;
                        }
                        len++;
                    }
                    conf.path = new char[len];
                    len = 0;
                    for (int j = 0; j < conf.y.length(); j++){
                        int t = conf.y.getTag(j);
                        if (!this.tagless && !this.useTnfa){
                            if (this.finreg){
                                if (t >= 0 && this.fixedTags){
                                    if (this.fix.bases[t] >= 0) continue;    // tag fixed to some other
                                }
                            } else {
                                if (t <= 0) continue;
                            }
                        } else {
                            if (t <= 0) continue;
                        }
                        conf.path[len++] = conf.y.charAt(j);
                    }
                }
            }
        }

        if (this.okui){
            this.paperGor1 = 0;
        }
    }
    /**
     * Deliver a string representing the closure data.
     *
     * @param      nfa TNFA
     * @param      topsort topsort queue
     * @param      sp index in it
     * @param      newpass newpass queue
     * @param      np index in it
     * @param      status status array
     * @param      result result array
     * @param      paths the visited paths
     * @return     string
     */

    private String showGoldRadStacksp1(TNFAStateTable nfa, TNFAstate[] topsort, int sp,
        TNFAstate[] newpass, int np, int[] status, int[] result, int[] paths){
        StringBuilder sb = new StringBuilder();
        sb.append("topsort: ");
        sb.append("[");
        for (int i = 0; i < sp; i++){
            if (i > 0) sb.append(" ");
            int n = topsort[i].number;
            sb.append(n);
            if (status[n] == TOPSORT){
                sb.append("t");
            } else if (status[n] == NEWPASS){
                sb.append("n");
            } else if (status[n] == ACTIVE){
                sb.append("a");
            }
            sb.append("(");
            int a = result[n];
            sb.append(a);
            if (a > 0){
                sb.append(",");
                sb.append(paths[a++]);
                sb.append(",");
                sb.append(paths[a++]);
            }
            sb.append(")");
        }
        sb.append("]");
        sb.append(" newpass:");
        sb.append("[");
        for (int i = 0; i < np; i++){
            if (i > 0) sb.append(" ");
            int n = newpass[i].number;
            sb.append(n);
            sb.append("(");
            int a = result[n];
            sb.append(a);
            if (a > 0){
                sb.append(",");
                sb.append(paths[a++]);
                sb.append(",");
                sb.append(paths[a++]);
            }
            sb.append(")");
        }
        sb.append("]");
        return sb.toString();
    }

    /**
     * Deliver the configurations describing the paths to the states reached from the specified
     * ones with arcs labelled with tags or prios. The DFS algorithm is used.
     * Discard paths whose Tstrings are not prior for the Posix policy.
     *
     * @param      nfa reference to the state table
     * @param      reached start states
     * @param      reached array of reached states
     * @param      paths encoded paths
     */

    private boolean closureDfs1(TNFAStateTable nfa, List<Config> reached,
        int[] result
        ,int[] pathTag
        ){
        if (visited == null || visited.length < nfa.stateNr){
            if (this.useTnfa && visited != null){
            }
            visited = new boolean[nfa.stateNr];
            topsort = new TNFAstate[nfa.stateNr];   // create stack
        } else {
            Arrays.fill(visited,false);
        }
        int sp = 0;
        boolean success = true;
        int nrconf = 0;
        this.pathsi = 2;
        doit: for (Config i : reached){
            TNFAstate n = i.q;
            if (visited[n.number]){
                success = false;
                break doit;
            }
            result[n.number] = --nrconf;
            topsort[sp++] = n;                         // push n
            while (sp > 0){                            // while stack not empty
                TNFAstate v = topsort[--sp];           // pop
                if (visited[v.number]){
                    success = false;
                    break doit;
                }
                visited[v.number] = true;
                // visit neighbours
                for (TNFAarc t = v.transList; t != null; t = t.next){
                    if (t.sym.kind == S_TAG || t.sym.kind == S_PRIO || t.sym.kind == S_NONE){
                        if (paths.length - this.pathsi < 2){
                            this.paths = Arrays.copyOf(paths,paths.length+100);
                            paths = this.paths;
                        }
                        int z = this.pathsi;
                        if (t.sym.kind == S_TAG){
                            paths[this.pathsi++] = t.sym.tag;
                            paths[this.pathsi++] = result[v.number];
                        } else {
                            z = result[v.number];
                        }
                        TNFAstate w = t.nextState;
                        if (visited[w.number]){
                            success = false;
                            break doit;
                        }
                        result[w.number] = z;
                        topsort[sp++] = w;               // push it
                    }
                }
            }
        }
        if (!success){
            Arrays.fill(result,0);
        }
        return success;
    }

    /** A reusable array of active states. */
    private boolean[] active;

    /** A reusable array of next transitions to visit. */
    private TNFAarc[] next;

    /**
     * Deliver the path reached from the specified state and next transition to visit
     * choosing the prior path if there is another one to the same state.
     *
     * @param      q state
     * @param      next next transitions to visit
     * @param      result array of resulting paths
     * @param      reached list of the starting configurations of the closure
     * @param      fromState starting state
     */

    private TNFAstate explore(TNFAstate q, TNFAarc[] next, int[] result,
        List<Config> reached, TDFAstate fromState
        ){
        for (TNFAarc t = next[q.number]; t != null; t = t.next){
            next[q.number] = t.next;
            if (t.sym.kind == S_TAG || t.sym.kind == S_PRIO || t.sym.kind == S_NONE){
                TNFAstate p = t.nextState;
                int x = this.pathsi;
                if (t.sym.kind == S_TAG){
                    if (paths.length - this.pathsi < 2){
                        this.paths = Arrays.copyOf(paths,paths.length+100);
                        paths = this.paths;
                    }
                    paths[this.pathsi++] = t.sym.tag;
                    paths[this.pathsi++] = result[q.number];
//Trc.out.printf("@@@@@ -- %s: %s %s q %s\n",this.pathsi-2,t.sym.tag,result[q.number],q.number);
                } else {
                    x = result[q.number];
                }
                int y = result[p.number];
                if (y == 0 ||                // never seen in this state
                    p.inDegree < 2 ||        // not a join point
                    lowerPOSIX(x,y,paths,reached,fromState)
                    ){
                    result[p.number] = x;
                    return p;
                }
                if (t.sym.kind == S_TAG){
                    this.pathsi = x;
                }
            }
        }
        return null;
    }

    // ---------- Okui's determinization -----------------

    /**
     * Deliver height of the specified tag.
     *
     * @param      tag tag
     * @return     height
     */

    private int height(int tag){
        if (tag < 0){
            tag = -tag;
            if ((tag & 1) != 0) tag++;        // act as closing
        }
        int h = this.tagHeight[tag];
        // TRACE(K,"height tag %s: %s\n",tag,h);
        return h;
    }

    /**
     * Tell if the specified first configuration is prior to the specified second one.
     *
     * @param      c1 first configuration
     * @param      c2 second configuration
     * @param      state starting state of them
     * @return     -1 if it is, >= 0 if not
     */

    private int compare_posix(Config c1, Config c2, TDFAstate state){
        int[][] bmatrix = null;
        int minTNFA = 0;
        if (state != null){
            bmatrix = state.bmatrix;
            minTNFA = state.minTNFA;
        }
        int res = 0;
        doit: {
            if (c1.origin == c2.origin || c1.origin.number == c2.origin.number){  // they can be null
                calc_rho_prec(c1.y,c2.y);
                res = RES_prec;
            } else {
                update_rho(c1,c2,bmatrix,minTNFA);
                if (RES_rho1 > RES_rho2){
                    res = -1;
                    break doit;
                }
                if (RES_rho1 < RES_rho2){
                    res = 1;
                    break doit;
                }
                int d = bmatrix[c1.order][c2.order] & 0x80000000;
                if (d < 0){
                    res = -1;
                    break doit;
                }
                if (d == 0){
                    res = 1;
                    break doit;
                }
                res = 0;
            }
        } // doit
        return res;
    }

    /** Result of rho comparison of first and second configurations.*/
    private int RES_rho1;

    /** Result of rho comparison of second and first configurations.*/
    private int RES_rho2;

    /** Result of previous comparisons.*/
    private int RES_prec;

    /**
     * Tell if the specified first configuration is prior to the specified second one.
     *
     * @param      c1 first configuration
     * @param      c2 second configuration
     * @param      state starti state of them
     * @return     -1 if it is, >= 0 if not
     */

    private void calc_rho_prec(Tstring a, Tstring b){
        // a and b contain tags, so they must be converted to their numbers
        doit: {
            RES_rho1 = INFINITE;
            RES_rho2 = INFINITE;
            RES_prec = 0;
if (a.equals(b)) break doit;
            int N = a.length();
            int M = b.length();
            // find fork
            int i = 0;
            while (i < N && i < M && a.charAt(i) == b.charAt(i)){
                i++;
            }
            // TRACE(K,"calc_rho_prec fork %s\n",i);

            // rhos
            // contrary to Okui, missing => infinite height
//            RES_rho1 = INFINITE;
//            RES_rho2 = INFINITE;
//            RES_prec = 0;
            // Okui's lastsp
            if (i > 0){
                RES_rho1 = height(a.getTag(i-1));
                RES_rho2 = RES_rho1;
            }
            // Okui's minsp
            for (int j = i; j < N; j++){
                int h = height(a.getTag(j));
                if (h < RES_rho1) RES_rho1 = h;
            }
            for (int j = i; j < M; j++){
                int h = height(b.getTag(j));
                if (h < RES_rho2) RES_rho2 = h;
            }
            // TRACE(K,"calc_rho_prec rho1 %s rho2 %s\n",RES_rho1,RES_rho2);
            // greater rho wins
            if (RES_rho1 > RES_rho2){
                RES_prec = -1;
                break doit;
            }
            if (RES_rho1 < RES_rho2){
                RES_prec = 1;
                break doit;
            }

            // TRACE(K,"calc_rho_prec i %s N %s M %s\n",i,N,M);
            // precedence
            // equal if and only if fork is at the very end
            if (i == N && i == M){
                RES_prec = 0;
                break doit;
            }
            // shorter wins
            if (i == N){
                RES_prec = -1;
                break doit;
            }
            if (i == M){
                RES_prec = 1;
                break doit;
            }
            // the one with the closing bracket wins
            // TRACE(K,"calc_rho_prec closing a %s b %s\n",(a.getTag(i) & 1) == 0,(b.getTag(i) & 1) == 0);

            int atag = a.getTag(i);
            int btag = b.getTag(i);
            if ((atag & 1) == 0){           // closing
                RES_prec = -1;
                break doit;
            }
            if ((btag & 1) == 0){           // closing
                RES_prec = 1;
                break doit;
            }
            // both are opening: negative wins
            // TRACE(K,"calc_rho_prec negative a %s b %s\n",a.getTag(i) > 0,b.getTag(i) > 0);
            if (atag > 0){
                RES_prec = -1;
                break doit;
            }
            if (btag > 0){
                RES_prec = 1;
                break doit;
            }
        } // doit
        //TRACE(K,"calc_rho_prec %s / %s res rho1 %s rho2 %s prec %s\n",a,b,RES_rho1,RES_rho2,RES_prec);
    }

    /**
     * Tell if the specified first Tstring is prior to the specified second one.
     *
     * @param      a first Tstring
     * @param      b second Tstring
     */

    private void calc_rho_prec_simpl(Tstring a, Tstring b){
        // TRACE(K,"calc_rho_prec %s / %s\n",a,b);
        // a and b contain tags, so they must be converted to their numbers
        doit: {
            int N = a.length();
            int M = b.length();
            // find fork
            int i = 0;
            while (i < N && i < M && a.charAt(i) == b.charAt(i)){
                i++;
            }
            // TRACE(K,"calc_rho_prec fork %s\n",i);

            // TRACE(K,"calc_rho_prec i %s N %s M %s\n",i,N,M);
            // precedence
            // equal if and only if fork is at the very end
            if (i == N && i == M){
                RES_prec = 0;
                break doit;
            }
            // shorter wins
            if (i == N){
                RES_prec = -1;
                break doit;
            }
            if (i == M){
                RES_prec = 1;
                break doit;
            }
            // the one with the closing bracket wins
            // TRACE(K,"calc_rho_prec closing a %s b %s\n",(a.getTag(i) & 1) == 0,(b.getTag(i) & 1) == 0);
            if ((a.getTag(i) & 1) == 0){           // closing
                RES_prec = -1;
                break doit;
            }
            if ((b.getTag(i) & 1) == 0){           // closing
                RES_prec = 1;
                break doit;
            }
            // both are opening: negative wins
            // TRACE(K,"calc_rho_prec negative a %s b %s\n",a.getTag(i) > 0,b.getTag(i) > 0);
            if (a.getTag(i) > 0){
                RES_prec = -1;
                break doit;
            }
            if (b.getTag(i) > 0){
                RES_prec = 1;
                break doit;
            }
        } // doit
        //TRACE(K,"calc_rho_prec %s / %s res rho1 %s rho2 %s prec %s\n",a,b,RES_rho1,RES_rho2,RES_prec);
    }

    /**
     * Deliver the rho values of the comparison of the specified configurations.
     *
     * @param      c1 first configuration
     * @param      c2 second configuration
     * @param      bmatrix bmatrix
     * @param      minTNFA offset of indexes in the bmatrix
     */

    private void update_rho(Config c1, Config c2, int[][] bmatrix, int minTNFA){
        RES_rho1 = bmatrix[c1.order][c2.order] & 0x7fffffff;
        RES_rho2 = bmatrix[c2.order][c1.order] & 0x7fffffff;
        // Okui's minsp
        for (int j = 0; j < c1.y.length(); j++){
            int h = height(c1.y.getTag(j));
            if (h < RES_rho1) RES_rho1 = h;
        }
        for (int j = 0; j < c2.y.length(); j++){
            int h = height(c2.y.getTag(j));
            if (h < RES_rho2) RES_rho2 = h;
        }
    }

    /** The minimum TNFA state number to access the bmatrix. */
    private int minTNFAstate;

    /** The reusable bmatrix of the previous state. Only for TNFA.  */
    private int[][] prevBmatrix;

    /**
     * Deliver the new, updated bmatrix comparing the specified configurations.
     *
     * @param      configs configurations to compare
     * @param      fromState state containing the previous bmatrix
     * @param      res resulting closure objec in which the new bmatrix is stored
     */

    private void update_bmatrix(List<Config> configs, TDFAstate fromState, XclosureResult res){
        int[][] bmatrix = null;
        if (fromState != null){
            bmatrix = fromState.bmatrix;
        }
        int N = configs.size();
        int M = 0;
        M = N;
        int m = 0;
        M++;
        int[][] bmatrixp = null;
        if (this.useTnfa){
            if (this.prevBmatrix == null || this.prevBmatrix.length < M){
                if (this.prevBmatrix != null){
                }
                this.prevBmatrix = new int[M][M];
            }
            bmatrixp = this.prevBmatrix;
        } else {
            bmatrixp = new int[M][M];
        }
        for (int i = 0; i < N; i++){
            Config c1 = configs.get(i);
            for (int j = 0; j < N; j++){
                Config c2 = configs.get(j);

                int dm = compare_posix(c1,c2,fromState);
                int c1n = i;
                int c2n = j;
                bmatrixp[c1n][c2n] = RES_rho1;
                bmatrixp[c2n][c1n] = RES_rho2;
                if (dm < 0){
                    bmatrixp[c1n][c2n] |= 0x80000000;
                } else {
                    bmatrixp[c2n][c1n] |= 0x80000000;
                }

            }
        }
        res.bmatrix = bmatrixp;
        if (this.useTnfa){
            this.prevBmatrix = bmatrix;
        }

    }

    private int compareConfigs(Config c1, Config c2, int[][] bmatrix){
        int res = 0;
        doit: {
            int rho1 = bmatrix[c1.order][c2.order] & 0x7fffffff;
            int rho2 = bmatrix[c2.order][c1.order] & 0x7fffffff;
            if (rho1 > rho2){
                res = -1;
                break doit;
            }
            if (rho1 < rho2){
                res = 1;
                break doit;
            }
            if (c1.origin == c2.origin || c1.origin.number == c2.origin.number){
                calc_rho_prec_simpl(c1.y,c2.y);
                res = RES_prec;
                break doit;
            } else {
                if (c1.order < c2.order){
                    res = -1;
                    break doit;
                }
                if (c1.order > c2.order){
                    res = 1;
                    break doit;
                }
                res = 0;
            } // doit
        }
        return res;
    }
    /**
     * Tell if the specified first path is prior to the specified second one.
     *
     * @param      l1 length of the first path
     * @param      l2 length of the second path
     * @param      o1 configuration at the start of the first path
     * @param      o2 configuration at the start of the second path
     * @param      state starting state of them
     * @return     -1 if it is, >= 0 if not
     */

    private int compare_posix(int l1, int l2, Config o1, Config o2, TDFAstate state){
        int[][] bmatrix = null;
        if (state != null){
            bmatrix = state.bmatrix;
        }
        int res = 0;
        int why = 0;
        doit: {
            int[] a = this.path1;
            int[] b = this.path2;
            boolean q1EQq2 = o1.origin == o2.origin || o1.origin.number == o2.origin.number;
            int h1 = INFINITE;
            int h2 = INFINITE;
            int k = 0;
            // find fork
            if (q1EQq2){
                // here we have also negative tags, they represent nil-trees
                while (k < l1 && k < l2 && a[k] == b[k]){
                    k++;
                }
                if (k > 0){
                    h1 = height(a[k-1]);
                    h2 = h1;
                }
            } else {
                int o1n = o1.order;
                int o2n = o2.order;
                h1 = bmatrix[o1n][o2n] & 0x7fffffff;
                h2 = bmatrix[o2n][o1n] & 0x7fffffff;
            }
            for (int j = k; j < l1; j++){
                int h = height(a[j]);
                if (h < h1) h1 = h;
            }
            for (int j = k; j < l2; j++){
                int h = height(b[j]);
                if (h < h2) h2 = h;
            }
            if (h1 > h2){
                res = -1;
                why = 1;
                break doit;
            }
            if (h1 < h2){
                res = 1;
                why = 2;
                break doit;
            }
            // leftmost precedence
            if (q1EQq2){
                if (k == l1 && k == l2){
                    res = 0;
                    why = 3;
                    break doit;
                }
                // shorter wins
                if (k == l1){
                    res = -1;
                    why = 4;
                    break doit;
                }
                if (k == l2){
                    res = 1;
                    why = 5;
                    break doit;
                }
                int atag = a[k];
                int btag = b[k];
                if ((atag & 1) == 0){           // closing
                    res = -1;
                    why = 6;
                    break doit;
                }
                if ((btag & 1) == 0){           // closing
                    res = 1;
                    why = 7;
                    break doit;
                }
                // both are opening: negative wins
                // if (atag > 0){
                if (atag > btag){
                    res = -1;
                    why = 8;
                    break doit;
                }
                // if (btag > 0){
                if (btag > atag){
                    res = 1;
                    why = 9;
                    break doit;
                }
            } else {
                int o1n = o1.order;
                int o2n = o2.order;
                res = bmatrix[o1n][o2n] & 0x80000000;
                why = 10;
            }
        } // doit
//Trc.out.printf("      compare posix %s\n",res);
        return res;
    }

    /**
     * Deliver a string representing the specified path.
     *
     * @param      p path
     * @param      l length of the significant part of it
     * @return     string
     */

    private String thispathToString(int[] p, int l){
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < l; i++){
            if (i > 0) sb.append(" ");
            sb.append(p[i]);
        }
        return sb.toString();
    }

    /**
     * Tell if the specified first path is prior to the specified second one.
     *
     * @param      a first path
     * @param      la its length
     * @param      b second path
     * @param      lb its length
     */

    private void calc_rho_prec(int[] a, int la, int[] b, int lb){
        // TRACE(K,"calc_rho_prec %s / %s\n",a,b);
        doit: {
            int N = la;
            int M = lb;
            // find fork
            int i = 0;
            while (i < N && i < M && a[i] == b[i]){
                i++;
            }
            // TRACE(K,"calc_rho_prec fork %s\n",i);

            // rhos
            // contrary to Okui, missing => infinite height
            RES_rho1 = INFINITE;
            RES_rho2 = INFINITE;
            RES_prec = 0;
            // Okui's lastsp
            if (i > 0){
                RES_rho1 = height(a[i-1]);
                RES_rho2 = RES_rho1;
            }
            // Okui's minsp
            for (int j = i; j < N; j++){
                int h = height(a[j]);
                if (h < RES_rho1) RES_rho1 = h;
            }
            for (int j = i; j < M; j++){
                int h = height(b[j]);
                if (h < RES_rho2) RES_rho2 = h;
            }
            // TRACE(K,"calc_rho_prec rho1 %s rho2 %s\n",RES_rho1,RES_rho2);
            // greater rho wins
            if (RES_rho1 > RES_rho2){
                RES_prec = -1;
                break doit;
            }
            if (RES_rho1 < RES_rho2){
                RES_prec = 1;
                break doit;
            }

            // TRACE(K,"calc_rho_prec i %s N %s M %s\n",i,N,M);
            // precedence
            // equal if and only if fork is at the very end
            if (i == N && i == M){
                RES_prec = 0;
                break doit;
            }
            // shorter wins
            if (i == N){
                RES_prec = -1;
                break doit;
            }
            if (i == M){
                RES_prec = 1;
                break doit;
            }
            // the one with the closing bracket wins
            // TRACE(K,"calc_rho_prec closing a %s b %s\n",(a[i] & 1) == 0,(b[i] & 1) == 0);

            int atag = a[i];
            int btag = b[i];
            if ((atag & 1) == 0){           // closing
                RES_prec = -1;
                break doit;
            }
            if ((btag & 1) == 0){           // closing
                RES_prec = 1;
                break doit;
            }
            // both are opening: negative wins
            // TRACE(K,"calc_rho_prec negative a %s b %s\n",a[i] > 0,b[i] > 0);
            if (atag > 0){
                RES_prec = -1;
                break doit;
            }
            if (btag > 0){
                RES_prec = 1;
                break doit;
            }
        } // doit
        //TRACE(K,"calc_rho_prec %s / %s res rho1 %s rho2 %s prec %s\n",a,b,RES_rho1,RES_rho2,RES_prec);
    }

    // ---------- Testing -----------------

    /** The name of the feature under testing. */
    private static String featureName;

    /** The flag to enable the trace of the tests. */
    private static boolean ckshow = false;

    /** The number of tests failed. */
    private static int testErrors;

    /**
     * Start the testing of a feature. Record its name and trace it
     * if the tracing of tests is enabled.
     *
     * @param      s feature name
     */

    private static void feature(String s){
        featureName = s;
        if (ckshow) Trc.out.printf("%s\n",featureName);
    }

    /**
     * Trace a test of a feature.
     *
     * @param      t number of the test
     */

    private static void showTest(int t){
        if (ckshow) Trc.out.printf("-- test %s %s ---\n",featureName,t);
    }

    /**
     * Report the failure of a test.
     *
     * @param      t number of the test
     */

    private static void trcfail(int t){
        Trc.out.printf("\n");
        Trc.out.printf("-- test %s %s failed---\n",featureName,t);
        testErrors++;
    }

    /**
     * Deliver the specified string with spaces removed.
     *
     * @param      str string
     * @return     string
     */

    private static String removeSpaces(String str){
        String s = "";
        for (int i = 0; i < str.length(); i++){
            if (str.charAt(i) == ' ') continue;
            s += str.charAt(i);
        }
        return s;
    }

    /**
     * Trace the specified message followed by the expected value and the actual one.
     *
     * @param      str message
     * @param      e expected value
     * @param      a actual value
     * @return     string
     */

    private static void trc(String s, String e, String a){
        Trc.out.printf("%s expected: |%s| actual: |%s|\n",s,e,a);
    }

    /**
     * Test that the AST built from the specified RE generates the same RE.
     *
     * @param      t number of the test case
     * @param      str RE
     * @param      exp expected generated RE ("error" if erroneous)
     */

    private void testAst(int t, String str, String exp){
        showTest(t);
        buildAst(str);
        String actual = "";
        if (this.error || getsym() != -1){    // error or whole re not consumed
            actual = "error";
        } else {
            actual = this.astRoot.toRE();
        }
        if (!removeSpaces(actual).equals(removeSpaces(exp))){
            trcfail(t);
            trc("re",exp,actual);
        }
        if (exp.equals("error")) return;
        // test the automatic generation of the TRE and its transformation into AST
        String tre = this.astRoot.toXTRE();
        buildAst(tre);
        if (this.error || getsym() != -1){    // error or whole re not consumed
            trcfail(t+1000);
            return;
        } else {
            actual = this.astRoot.toRE();
        }
        if (!removeSpaces(actual).equals(removeSpaces(tre))){
            trcfail(t+2000);
            trc("re",tre,actual);
        }
    }

    private void testAstTree(int t, String str, String exp){
        showTest(t);
        buildAst1(str);
        String actual = "";
        if (this.error || getsym() != -1){    // error or whole re not consumed
            actual = "error";
        } else {
            actual = this.astRoot.toTree();
        }
        if (!actual.equals(exp)){
            trcfail(t);
            trc("ast",exp,actual);
        }
    }

    /**
     * Test that the TNFA built from the specified RE generates the expected TNFA.
     *
     * @param      t number of the test case
     * @param      str RE
     * @param      exp expected generated TNFA
     */

    private void testTNFA(int t, String str, String exp){
        showTest(t);
        buildAst(str);
        if (this.error || getsym() != -1){    // error or whole re not consumed
            trcfail(t);
        }
        TNFAStateTable nfa = buildTNFA(this.astRoot);
        String actual = nfa.toString();
        TNFAStateTable other = new TNFAStateTable();
        other.stringToGraph(exp);
        boolean iso = nfa.isIsomorphic(other);
        String expected = other.toString();
        if (!iso){
            trcfail(t+1000);
        }
        if (!actual.equals(expected)){
            trcfail(t+2000);
            trc("nfa",expected,actual);
            Trc.out.printf("%s\n",optionsString());
        }
    }

    /**
     * Test that the specified text matches the specified RE and generates the expected tree.
     *
     * @param      t number of the test case
     * @param      str RE
     * @param      text text
     * @param      exp expected generated tree
     * @param      expg expected generated greedy tree
     * @param      expp expected generated partial tree
     */

    private void testTree(int t, String str, String text, String exp, String expg, String expp){
        showTest(t);
        if (expg == null) expg = exp;
        boolean save = this.posix;
        testTreeInternal(t,str,text,exp,this.testTreeAlgos,true);
        testTreeInternal(t,str,text,expg,this.testTreeAlgos,false);
        this.posix = save;
        if (expp != null){
            testTreeInternal(t,str,text,expp,this.testTreeAlgosPar,true);
        }
        if (!exp.equals("error")){
            testOffsetsInternal(t,str,text,this.testTreeAlgos,false,true);
            testOffsetsInternal(t,str,text,this.testTreeAlgos,true,true);
            testOffsetsInternal(t,str,text,this.testTreeAlgos,false,false);
            testOffsetsInternal(t,str,text,this.testTreeAlgos,true,false);
        }
    }

    private void testTree(int t, String str, String text, String exp, String expg){
        testTree(t,str,text,exp,expg,null);
    }
    private void testTree(int t, String str, String text, String exp){
        testTree(t,str,text,exp,exp,exp);
    }

    /** The total number of configurations. */
    private static int totconfig;

    /** The algorithms to test. */
    private String[] testTreeAlgos = new String[]{
        "nfa","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa",
        "incr","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa,incremental",
        "base","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,bijCyclic",
        "+trie","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable",
        "+acyc","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,regTrie",
        "+look","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,regTrie,lookahead",
        "+fix","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,regTrie,lookahead,fixedTags",
        "tagless","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,lookahead,tagless",
        "finreg","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,lookahead,tagless,finreg",
        "finreg-fix","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,lookahead,tagless,finreg,fixedTags",
        "onepass","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,lookahead,tagless,onepass",
        "tree","negtags=inherit,autotags,altbin=inherit,posix=inherit,transtable,lookahead,matchTstring,tagless",
        "okui","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,transtable,bijCyclic,okui",
        "okui-tless","negtags=inherit,autotags,altbin=inherit,posix=inherit,transtable,bijCyclic,lookahead,tagless,matchTstring,okui",
//        "okui-tless0","negtags=inherit,autotags,altbin=inherit,posix=inherit,transtable,bijCyclic,tagless,matchTstring,okui",
        "okui-nfa","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa,okui",
        "okui-incr","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa,incremental,okui",
        "okui-incr-tless","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa,incremental,okui,tagless",
        "nfa1","negtags=inherit,autotags,altbin=inherit,posix=inherit,matchTstring,useTnfa,finreg",
        "fix","negtags=inherit,altbin=inherit,posix=inherit,transtable,lookahead,okui,autotags,matchTstring,finreg,fixedTags",
        "-fix","negtags=inherit,altbin=inherit,posix=inherit,transtable,lookahead,okui,autotags,matchTstring,finreg",
        };
    private String[] testTreeAlgosPar = new String[]{
        "okui-part","negtags=inherit,altbin=inherit,posix=inherit,transtable,bijCyclic,matchTstring,lookahead,okui",
        "okui-tless-part","negtags=inherit,altbin=inherit,posix=inherit,transtable,bijCyclic,matchTstring,lookahead,tagless,okui",
        };

    private void testTreeInternal(int t, String str, String text, String exp, String[] algos,
        boolean posix){
        String actual = "";
        for (int i = 0; i < algos.length; i += 2){
            String name = algos[i] + "-" + (posix ? "posix" : "greedy");
            String opt = algos[i+1];
            this.posix = posix;
            setOptions(name,opt);
            if (this.parsetree && this.tagless && !this.onepass){
                this.parsetree = true;
            }
            if (this.okui && !posix) continue;
            compile(str);
            if (this.error){
                if (!exp.equals("error")){
                    trcfail(t);
                    trc("compile " + name,exp,"error");
                    Trc.out.printf("%s\n",optionsString());
                }
                continue;
            }
            totconfig += this.confSeq;
            match(text);
            if (this.error){
                if (!exp.equals("error")){
                    trcfail(t);
                    trc("match " + name,exp,"error");
                    Trc.out.printf("%s\n",optionsString());
                }
                continue;
            }
            if (this.autotags || this.newTNFA){
/*
                if (this.parsetree){
                    StringBuilder sb = new StringBuilder();
//                    treeToLst(sb,1,text);
                    treeToString(sb,1,text);
                    actual = sb.toString();
                } else {
                    actual = toLST();
                }
*/
                actual = toLST();
                if (!actual.equals(exp)){
                    trcfail(t);
                    trc("tree " + name,exp,actual);
                    Trc.out.printf("%s\n",optionsString());
                    //tdfa.trace();
                    continue;
                }

                if (this.parsetree && this.tagless && !this.onepass){
                    actual = treeToString(text);
                    StringBuilder sb = new StringBuilder();
                    for (int j = 0; j < exp.length(); j++){
                        char ch = exp.charAt(j);
                        if (ch == '(' || ch == ')' || 'a' <= ch && ch <= 'z'){
                            sb.append(ch);
                        }
                    }
                    String expect = sb.toString();
                    if (!actual.equals(expect)){
                        trcfail(t+1000);
                        trc("tree " + name,expect,actual);
                        Trc.out.printf("%s\n",optionsString());
                        traceDOM();
                        continue;
                    }
                }
            }
        }
    }

    private void testOffsetsInternal(int t, String re, String text, String[] algos,
        boolean trie, boolean full){
        ReTdfa rt = new ReTdfa();
        rt.setOptions("ref","negtags,posix,matchTstring,finreg,useTnfa");
        if (full){
            rt.autotags = true;
        } else {
            rt.okui = true;
        }
        if (!rt.compile(re)){
            trcfail(t);
            Trc.out.printf("!! RE %s %s compile ref error\n",re,rt.name);
            return;
        }
        if (!rt.match(text)){
            trcfail(t);
            Trc.out.printf("!! match tree ref error\n");
            return;
        }
        for (int i = 0; i < algos.length; i += 2){
            String name = algos[i] + "-offsets";
            String opt = algos[i+1];
            ReTdfa rt1 = new ReTdfa();
            rt1.setOptions(name,opt);
            rt1.posix = true;
            rt1.finreg = true;
            rt1.subhist = true;
            rt1.xcomp = true;
            rt1.negtags = true;
            if (trie){
                rt1.regTrie = true;
                rt1.bijCyclic = false;
            } else {
                rt1.regTrie = false;
            }
            if (full){
                rt1.autotags = true;
            } else {
                rt1.autotags = false;
                rt1.okui = true;
            }
            boolean b = rt1.compile(re);
            if (!b){
                trcfail(t);
                Trc.out.printf("!! RE %s %s compile error\n",re,rt1.name);
                continue;
            }
            b = rt1.match(text);
            if (!b){
                trcfail(t);
                Trc.out.printf("!! match tree error\n");
                Trc.out.printf("    RE %s\n",rt1.re);
                Trc.out.printf("    text %s\n",text);
                continue;
            }
            if (!rt.toLST().equals(rt1.toLST()) ||
                !deepEquals(rt.finalRegisters,rt1.finalRegisters,rt.nrTags+1)){
                trcfail(t);
                Trc.out.printf("!! compare error\n");
                Trc.out.printf("    RE %s\n",rt.re);
                Trc.out.printf("    text %s\n",text);
                Trc.out.printf("    %s %s\n",rt.name,rt.toLST());
                if (!rt.toLST().equals(rt1.toLST())){
                    Trc.out.printf("    %s %s\n",rt1.name,rt1.toLST());
                }
                Trc.out.printf("    %s %s\n",rt.name,Arrays.deepToString(rt.finalRegisters));
                if (!deepEquals(rt.finalRegisters,rt1.finalRegisters,rt.nrTags+1)){
                    Trc.out.printf("    %s %s\n",rt1.name,Arrays.deepToString(rt1.finalRegisters));
                }
                Trc.out.printf("    first %s\n",rt.optionsString());
                Trc.out.printf("    second %s\n",rt1.optionsString());
                Trc.out.printf("    first nfa %s\n",rt.nfa.toString());
                if (rt1.nfa != null){
                    if (!rt.nfa.toString().equals(rt1.nfa.toString())){
                        Trc.out.printf("    second nfa %s\n",rt1.nfa.toString());
                    }
                }
                continue;
            }
        }
    }

    /** Algorithms to deliver the final registers for full parsing. */
    private String[] testFinregAlgos = new String[]{
        "tdfa","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg",
        "tdfa-okui","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui",
        "tdfa-okui-tagless","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless",
        "tdfa-okui-tagless1","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless,onepass",

        "tnfa","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,useTnfa",
        "tnfa-okui","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,useTnfa",
        "tnfa-okui-tagless","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless,useTnfa",
        "tnfa-okui-tagless1","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless,onepass,useTnfa",

        "tnfai","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,useTnfa,incremental",
        "tnfai-okui","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,useTnfa,incremental",
        "tnfai-okui-tagless","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless,useTnfa,incremental",
        "tnfai-okui-tagless1","negtags,posix,transtable,lookahead,autotags,matchTstring,finreg,okui,tagless,onepass,useTnfa,incremental",
        };

    /** Algorithms to deliver the final registers for partial parsing. */
    private String[] testFinregPartAlgos = new String[]{
        "tdfa","negtags,posix,transtable,lookahead,matchTstring,finreg",
        "tdfa-okui","negtags,posix,transtable,lookahead,matchTstring,finreg,okui",
        "tdfa-okui-tagless","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless",
        "tdfa-okui-tagless1","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless,onepass",

        "tnfa","negtags,posix,transtable,lookahead,matchTstring,finreg,useTnfa",
        "tnfa-okui","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,useTnfa",
        "tnfa-okui-tagless","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless,useTnfa",
        "tnfa-okui-tagless1","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless,onepass,useTnfa",

        "tnfai","negtags,posix,transtable,lookahead,matchTstring,finreg,useTnfa,incremental",
        "tnfai-okui","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,useTnfa,incremental",
        "tnfai-okui-tagless","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless,useTnfa,incremental",
        "tnfai-okui-tagless1","negtags,posix,transtable,lookahead,matchTstring,finreg,okui,tagless,onepass,useTnfa,incremental",
        };

    /**
     * Test that the specified text matches the specified RE and generates the same final
     * registers as the first algorithm.
     *
     * @param      t number of the test case
     * @param      str RE
     * @param      text text
     * @param      algos algorithms
     */

    private void testFinreg(int t, String str, String text, String[] algos){
        showTest(t);
        String lst = null;
        int[][] finalregs = null;
        for (int i = 0; i < algos.length; i += 2){
            String name = algos[i];
            String opt = algos[i+1];
            setOptions(name,opt);
            compile(str);
            if (this.error){
                trcfail(t);
                Trc.out.printf("compile error %s\n",optionsString());
                continue;
            }
            match(text);
            if (this.error){
                trcfail(t);
                Trc.out.printf("match error %s\n",optionsString());
                continue;
            }
            if (i == 0){
                lst = toLST();
                finalregs = new int[this.nrTags+1][];
                for (int j = 0; j < finalregs.length; j++){
                    if (this.finalRegisters[j] == null) continue;
                    finalregs[j] = Arrays.copyOf(this.finalRegisters[j],this.finalRegisters[j].length);
                }
            } else {
                if (!toLST().equals(lst) ||
                    !deepEquals(finalregs,this.finalRegisters,this.nrTags+1)){
                    trcfail(t);
                    Trc.out.printf("!! compare error\n");
                    Trc.out.printf("    RE %s\n",this.re);
                    Trc.out.printf("    text %s\n",this.text);
                    Trc.out.printf("    base %s %s\n",algos[0],algos[1]);
                    Trc.out.printf("    base %s\n",lst);
                    Trc.out.printf("    second %s %s\n",name,optionsString());
                    Trc.out.printf("    second %s\n",toLST());
                    Trc.out.printf("    base %s\n",Arrays.deepToString(Arrays.copyOf(finalregs,this.nrTags+1)));
                    Trc.out.printf("    second %s\n",Arrays.deepToString(Arrays.copyOf(this.finalRegisters,this.nrTags+1)));
                    // System.exit(1);
                    continue;
                }
            }
        }
    }


    private void testResult(int t, String opt){
        showTest(t);
        setOptions("",opt);
        if (!compile("a(b)c")){
            trcfail(t);
            Trc.out.printf("compile error\n");
        }
        this.treeLen = 0;
        this.finalRegisters = null;
        if (!match("abc")){
            trcfail(t);
            Trc.out.printf("match error\n");
        }
        if (this.matchTstring){
            if (!this.toLST().equals("(∧(1a1)1(2(2.1b2.1)2.1)2(3c3)3)∧⊣$")){
                trcfail(t);
                Trc.out.printf("lst error\n");
            }
        }
        if (this.finreg){
            if (submatches().equals("[[(0,12)][(1,3)][(4,8)][(5,7)][(9,11)]]")){
                trcfail(t);
                Trc.out.printf("finreg error\n");
            }
        }
    }

    /**
     * Test that the specified text matches anywhere the specified RE and generates the
     * expected tree.
     *
     * @param      t number of the test case
     * @param      str RE
     * @param      text text
     * @param      exp expected generated tree
     */

    private void testFowler(int t, String str, String text, String exp){
        showTest(t);
        String actual = "";
        doit: {
            buildAst(str);
            TNFAStateTable nfa = null;
            if (!this.error) nfa = buildTNFA(this.astRoot);
            if (this.error || getsym() != -1){    // error or whole re not consumed
                break doit;
            }
            this.useTnfa = true;
            actual = findAnywhere(nfa,text);
        }
        if (!actual.equals(exp)){
            trcfail(t);
            trc("offsets",exp,actual);
        }
    }

    private void testRE2C(int t, String re, String text, String exp) {
        showTest(t);
        String actual = "";

        long reg = RE2C.regcomp(re, this.re2c_nfa, this.re2c_regless, false, false, false);
        if (reg == 0) {
            System.out.printf("regcomp failed on RE %s\n", re);
        }

        int e = RE2C.regexec(reg, text);
        if (e != 0) {
            System.out.printf("NOMATCH (error code %d)\n", e);
        }

        for (int i = 0; i < RE2C.getNmatch(reg); ++i) {
            long x = RE2C.getStartOffset(reg, i);
            long y = RE2C.getEndOffset(reg, i);
            String sx = x == -1 ? "?" : String.valueOf(x);
            String sy = y == -1 ? "?" : String.valueOf(y);
            actual += '(' + sx + ',' + sy + ')';
        }

        RE2C.regfree(reg);

        if (!actual.equals(exp)){
            trcfail(t);
            trc("offsets",exp,actual);
        }
    }

    /**
     * Test the operations on boolean sets.
     */

    private void testBoolSetAssign(int t, String str){
        showTest(t);
        String s = "0:" + str + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set = new BoolSet();
        set.assignArr(st.head.transList.sym.symset);
        String actual = "["+ set.toString() + "]";
        if (!actual.equals(str)){
            trcfail(t);
            trc("set",str,actual);
        }
        BoolSet set1 = new BoolSet();
        set1.assignSet(set);
        actual = "["+ set1.toString() + "]";
        if (!actual.equals(str)){
            trcfail(t+1000);
            trc("set",str,actual);
        }
    }
    private void testBoolSetRange(int t, int l, int h, String exp){
        showTest(t);
        BoolSet set = new BoolSet();
        set.addRange(l,h);
        String actual = "["+ set.toString() + "]";
        if (!actual.equals(exp)){
            trcfail(t);
            trc("set",exp,actual);
        }
    }
    private void testBoolSetSet(int t, int e, boolean v, String exp){
        showTest(t);
        BoolSet set = new BoolSet();
        set.set(e,v);
        String actual = "["+ set.toString() + "]";
        if (!actual.equals(exp)){
            trcfail(t);
            trc("set",exp,actual);
        }
        set.clear();
        if (!set.toString().equals("")){
            trcfail(t+1000);
            trc("set","",set.toString());
        }
    }
    private void testBoolSetComp(int t, String str){
        showTest(t);
        String s = "0:" + str + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set = new BoolSet();
        set.assignArr(st.head.transList.sym.symset);
        set.complement();
        String actual = "[^" + symSetToString(set.arr,false) + "]";
        s = "[^" + str.substring(1);
        if (!actual.equals(s)){
            trcfail(t);
            trc("set",s,actual);
        }
    }

    private void testBoolSetOper(int t, String s1, String op, String s2, String exp){
        showTest(t);
        String s = "0:" + s1 + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set1 = new BoolSet();
        set1.assignArr(st.head.transList.sym.symset);
        s = "0:" + s2 + "->1";
        st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set2 = new BoolSet();
        set2.assignArr(st.head.transList.sym.symset);
        if (op.equals("or")){
            set1.or(set2);
        } else if (op.equals("and")){
            set1.and(set2);
        } else if (op.equals("sub")){
            set1.sub(set2);
        }
        String actual = "["+ set1.toString() + "]";
        if (!actual.equals(exp)){
            trcfail(t);
            trc("set",exp,actual);
        }
    }
    private void testBoolSetEmpty(int t, String str, boolean exp){
        showTest(t);
        String s = "0:" + str + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set = new BoolSet();
        set.assignArr(st.head.transList.sym.symset);
        if (set.isEmpty() != exp){
            trcfail(t);
        }
    }
    private void testBoolSetEquals(int t, String s1, String s2, boolean exp){
        showTest(t);
        String s = "0:" + s1 + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set1 = new BoolSet();
        set1.assignArr(st.head.transList.sym.symset);
        s = "0:" + s2 + "->1";
        st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set2 = new BoolSet();
        set2.assignArr(st.head.transList.sym.symset);
        boolean actual = set1.equals(set2);
        if (actual != exp){
            trcfail(t);
        }
        BoolSet set3 = set2.clone();
        actual = set1.equals(set2);
        if (actual != exp){
            trcfail(t+1000);
        }
    }
    private void testBoolSetCompare(int t, String s1, String s2, int exp){
        showTest(t);
        String s = "0:" + s1 + "->1";
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set1 = new BoolSet();
        set1.assignArr(st.head.transList.sym.symset);
        s = "0:" + s2 + "->1";
        st = new TNFAStateTable();
        st.stringToGraph(s);
        BoolSet set2 = new BoolSet();
        set2.assignArr(st.head.transList.sym.symset);
        int actual = set1.compareTo(set2);
        if (actual != exp){
            trcfail(t);
            trc("res",Integer.toString(exp),Integer.toString(actual));
        }
    }

    /**
     * Test that the character classes in the specified FA are the expected ones.
     *
     * @param      t number of the test case
     * @param      str FA
     * @param      exp expected classes
     */

    private void testSymClass(int t, String str, String exp){
        showTest(t);
        TNFAStateTable st = new TNFAStateTable();
        st.stringToGraph(str);
        this.nfa = st;
        buildSymClass();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.symClassTable.length; i++){
            if (sb.length() > 0) sb.append(",");            
            sb.append(this.symClassTable[i]);
        }
        String actual = sb.toString();
        if (!actual.equals(exp)){
            trcfail(t);
            trc("set",exp,actual);
        }
    }

    private int testtrieappend(int t, String str, String es, TstringTrie tr, int prev){
        showTest(t);
        Tstring ts = new Tstring();
        ts.append(str.toCharArray());
        int idx = tr.append(prev,ts);
        String as = tr.toTstring(idx ).toString();
        if (!as.equals(es)){
            trcfail(t);
            trc("string",es,as);
        }
        return idx;
    }
    // Benchmarks

    /** The name of the samples file. */
    private static final String SAMPLES = "samples4.ser";

    /** The numeric suffix of the measures and chart files. */
//    private static final String WNUMBER = "9";
//    private static final String WNUMBER = "18";     // non _sep
//    private static final String WNUMBER = "19";     // _sep
    private static final String WNUMBER = "20";     // _sep tnfa
//    private static final String WNUMBER = "21";     // _sep tdfa

    /** The name of the measurements file for 0:1K texts. */
    private static final String MEA100 = "measure100TDFA" + WNUMBER + ".ser";

    /** The name of the charts file. */
    private static final String CHARTMEA = "reTdfaChartmea" + WNUMBER + ".html";

    /** The unit length of texts. */
    private static final int TEXT_SAMPLES_LENGTH = 100;

    /** The samples. */
    private class Samples {
        String[][] res;
        String[][][][] texts;

        private void read(String file){
            this.res = new String[10][];
            this.texts = new String[res.length][][][];
            try {
                FileInputStream fileIn = new FileInputStream(file);
                ObjectInputStream in = new ObjectInputStream(fileIn);
                res = (String[][])in.readObject();
                texts = (String[][][][])in.readObject();
                in.close();
                fileIn.close();
                System.out.printf("benchmark samples read: %s\n",file);
            } catch(FileNotFoundException exc){
                exc.printStackTrace();
                System.out.printf("%s\n",exc);
                System.exit(1);
            } catch(IOException exc){
                exc.printStackTrace();
                System.out.printf("%s\n",exc);
                System.exit(1);
            } catch(ClassNotFoundException c){
                System.out.printf("samples not found\n");
                System.exit(1);
            }
        }
    }

    private static boolean deepEquals(int[][] v1, int[][] v2, int len){
        if (v1 == null && v2 == null) return true;
        if (v1.length < len || v2.length < len) return false;
        for (int i = 0; i < len; i++){
            if (!Arrays.equals(v1[i],v2[i])) return false;
        }
        return true;
    }

    private boolean equalTrees(ReTdfa r1,ReTdfa r2){
        if (r1.treeLen != r2.treeLen){
            return false;
        }
        for (int i = 0; i < r1.treeLen; i++){
            if (r1.treearr[i] != r2.treearr[i]){
                return false;
            }
        }
        return true;
    }

    private AstNode toNewAst(String re){
        ReTdfa rt = new ReTdfa();
        rt.negtags = true;
        rt.altbin = true;
        rt.noGRO = false;
        rt.autotags = true;
        rt.posix = true;
        String ret = re.replaceAll("\\[","(");
        ret = ret.replaceAll("\\]",")?");
        rt.buildAst(ret);
        if (this.error || getsym() != -1){    // error or whole re not consumed
            Trc.out.printf("!! RE error\n",re);
            return null;
        }
        // generate the other with the [] instead of ()? and binary |
        return rt.astRoot;
    }

    private String toOldRE(AstNode ast){
        String str = "";
        if (ast.kind == A_LEA){          // leaf
            str += " ";
            str += ast.sym;
        } else if (ast.kind == A_ALT){   // alt
            for (AstNode i = ast.son; i != null; i = i.bro){
                if (i != ast.son) str += " |";
                if (i.kind == A_ALT){
                    str += "(";
                }
                str += toOldRE(i);
                if (i.kind == A_ALT){
                    str += ")";
                }
            }
        } else if (ast.kind == A_CON){   // conc
            for (AstNode i = ast.son; i != null; i = i.bro){
                if (i.kind == A_ALT || i.kind == A_CON){
                    str += "(";
                }
                str += toOldRE(i);
                if (i.kind == A_ALT || i.kind == A_CON){
                    str += ")";
                }
            }
        } else if (ast.kind == A_EMP){   // empty
        } else if (ast.kind == A_NUL){   // empty set
        } else {                         // group
            if (ast.groupKind == G_OPT){
                str += "[";
            } else {
                str += "(";
            }
            if (ast.son != null){
                str += toOldRE(ast.son);
                if (ast.groupKind == G_OPT){
                    str += "]";
                } else {
                    str += ")";
                }
            }
            if (ast.groupKind != G_OPT){
                str += groupSym[ast.groupKind];
            }
        }
        return str;
    }

    /**
     * Run the benchmark.
     */

    private void benchmark(){
        ReTdfa[] rearr = new ReTdfa[]{
            new ReTdfa("base","negtags,altbin,noGRO,autotags,posix,transtable,bijCyclic"),
            new ReTdfa("+trie","negtags,altbin,noGRO,autotags,posix,transtable"),
            new ReTdfa("+acyc","negtags,altbin,noGRO,autotags,posix,transtable,regTrie"),
            new ReTdfa("+look","negtags,altbin,noGRO,autotags,posix,transtable,regTrie,lookahead"),
            new ReTdfa("+fix","negtags,altbin,noGRO,autotags,posix,transtable,regTrie,lookahead,fixedTags")};
        bench(rearr);
    }

    /**
     * Measures the compilation and parse speed and memory footprint for the configured samples
     * and all the specified algorithms.
     *
     * @param      reTest array of algorithms
     * @param      mfile name of the measure file
     */

    private void benchMeasure(ReTdfa[] reTest, String mfile){
        for (int i = 0; i < reTest.length; i++){
            Trc.out.printf("%s options: %s\n",i,reTest[i].optionsToString());
        }
        // read the samples
        Samples samp = new Samples();
        samp.read(SAMPLES);
        String[][] res = samp.res;
        String[][][][] texts = samp.texts;

        // allocate
        long[][][][] matrc = new long[res.length][][][];        // compile times
        long[][][][] matrp = new long[res.length][][][];        // parse times
        long[][][][] matrm = new long[res.length][][][];        // memory
        long[][][][] matrf = new long[res.length][][][];        // FA size
        for (int i = 0; i < res.length; i++){                   // for all REs buckets
            matrc[i] = new long[res[i].length][][];
            matrp[i] = new long[res[i].length][][];
            matrm[i] = new long[res[i].length][][];
            matrf[i] = new long[res[i].length][][];
            for (int j = 0; j < matrp[i].length; j++){             // for all REs in bucket
                matrc[i][j] = new long[1][];
                for (int k = 0; k < matrc[i][j].length; k++){      // for all its text buckets
                    matrc[i][j][k] = new long[reTest.length];
                    Arrays.fill(matrc[i][j][k],Long.MAX_VALUE-1);
                }
                matrf[i][j] = new long[2][];
                for (int k = 0; k < matrf[i][j].length; k++){      // for all its text buckets
                    matrf[i][j][k] = new long[reTest.length];
                    Arrays.fill(matrf[i][j][k],Long.MAX_VALUE-1);
                }
                matrp[i][j] = new long[texts[i][j].length][];
                matrm[i][j] = new long[texts[i][j].length][];
                for (int k = 0; k < matrp[i][j].length; k++){      // for all its text buckets
                    matrp[i][j][k] = new long[reTest.length];
                    matrm[i][j][k] = new long[reTest.length];
                    Arrays.fill(matrp[i][j][k],Long.MAX_VALUE-1);
                    Arrays.fill(matrm[i][j][k],Long.MAX_VALUE-1);
                }
            }
        }

        System.out.printf("benchmeasure\n");
        int nres = 0;
        int ntexts = 0;
        // measure
//        for (int m = 0; m < 3; m++){
        for (int m = 0; m < 1; m++){
//            for (int i = 0; i < matrp.length; i++){                 // for each re bucket
            for (int i = 0; i < 8; i++){                 // for each re bucket
                for (int j = 0; j < matrp[i].length; j++){          // for all REs in bucket
                    String re = res[i][j];
                    if (re == null){
                        System.out.printf("!! null RE %s.%s\n",i,j);
                        System.exit(1);
                    }
                    String ren = re.replaceAll("\\[","(");
                    ren = ren.replaceAll("\\]",")?");
                    for (int a = 0; a < reTest.length; a++){        // for all variants of algorithm
                        long t0 = 0;
                        long t1 = 0;
                        long ti = 0;
                        System.gc();

                        // compile
                        System.out.printf("compile algo %s: %s re %s.%s",a,reTest[a].name,i,j);
                        //Trc.out.printf("compile algo %s re %s.%s\n",a,i,j);

//                        matrf[i][j][0][a] = 0;
//                        matrf[i][j][1][a] = 0;
                        ReTdfa regex = new ReTdfa();
                        regex.copyOptions(reTest[a]);
                        for (int n = 0; n < 10; n++){               // make a valid measure
                            nres++;
                            t0 = System.nanoTime();
                            if (!regex.compile(ren)){
                                System.out.printf("!! RE error\n",ren);
                                System.exit(1);
                            }
                            t1 = System.nanoTime();
                            ti = t1 - t0 - NANO_BASE;
                            if (ti > 0) break;
                        }
                        if (ti <= 0){
                            System.out.printf("!! bad measure\n");
                            System.exit(1);
                            ti = 0;
                        }
                        if (ti < matrc[i][j][0][a]){
                            matrc[i][j][0][a] = ti;
                        }
                        System.out.printf(".. done parse now");
                        // parse all text buckets of this RE
if (a == 0) Trc.out.printf("RE %s %s",i,j);
                        for (int k = 0; k < matrp[i][j].length; k++){    // for all its text buckets
                            regex.clear(); // clear the memory
                            long fpmax = 0;
                            String[] tbdir = texts[i][j][k];
                            if (tbdir == null){
                                System.out.printf("!! null text %s.%s.%s\n",i,j,k);
                                System.exit(1);
                            }
//System.out.printf(" text bucket %s\n",k);
                            for (int n = 0; n < 10; n++){            // make a valid measure
                                ntexts++;
                                t0 = System.nanoTime();
                                for (int l = 0; l < tbdir.length; l++){
                                    if (!regex.match(tbdir[l])){
                                        System.out.printf(" error parse text: %s.%s.%s.%s\n",i,j,k,l);
                                        System.out.printf(" error parse RE: %s text: %s\n",ren,tbdir[l]);
                                        System.out.printf(" options %s\n",regex.optionsString());
                                        System.out.printf(" %s\n",regex.nfa.toString());
                                        traceAst(regex.astRoot);
                                        System.exit(1);
                                    }
                                }
                                t1 = System.nanoTime();
                                ti = t1 - t0 - NANO_BASE;
                                if (ti > 0) break;
System.out.printf("invalid measure\n");
                            }
                            if (ti <= 0){
                                System.out.printf("!! bad measure\n");
                                System.exit(1);
                            }
                            if (ti < matrp[i][j][k][a]){
                                matrp[i][j][k][a] = ti;
                                matrm[i][j][k][a] = 0;
                                //Trc.out.printf("end bucket mem %s toks %s\n",regex.memory,regex.tokens);
                            }
                        }
if (a == 0) Trc.out.printf("\n");

                        int ntags;
                        if (regex.re2c) {
                            ntags = RE2C.getNtags(regex.re2c_reg);
                        } else {
                            ntags = regex.nrTags;
                        }
                        System.out.printf(".. done (%d tags)\n", ntags);

                        if (this.re2c) {
                            RE2C.regfree(this.re2c_reg);
                        }
                    }
                }
            }
        }

        // output the measure
        try {
            FileOutputStream fileOut = new FileOutputStream(mfile);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(matrc);
            out.writeObject(matrp);
            out.writeObject(matrm);
            out.writeObject(matrf);
            out.close();
            fileOut.close();
        } catch(IOException exc){
            System.out.printf("serialization %s\n",exc);
        }
        System.out.printf("REs compilations %s texts parsed %s\n",nres,ntexts);
    }

    /**
     * Copies all the options from the specified object into this one.
     *
     * @param      r other RE
     */

    private void copyOptions(ReTdfa r){
        this.name = r.name;
        this.negtags = r.negtags;
        this.altbin = r.altbin;
        this.concbin = r.concbin;
        this.noGRO = r.noGRO;
        this.autotags = r.autotags;
        this.posix = r.posix;
        this.matchTstring = r.matchTstring;
        this.lookahead = r.lookahead;
        this.bijCyclic = r.bijCyclic;
        this.transtable = r.transtable;
        this.regTrie = r.regTrie;
        this.fixedTags = r.fixedTags;
        this.incremental = r.incremental;
        this.useTnfa = r.useTnfa;
        this.tagless = r.tagless;
        this.finreg = r.finreg;
        this.subhist = r.subhist;
        this.xcomp = r.xcomp;
        this.offsets = r.offsets;
        this.lastval = r.lastval;
        this.onepass = r.onepass;
        this.parsetree = r.parsetree;
        this.okui = r.okui;
        this.dfsClosure = r.dfsClosure;
        this.onetag = r.onetag;
        this.re2c = r.re2c;
        this.re2c_nfa = r.re2c_nfa;
        this.re2c_jit = r.re2c_jit;
        this.re2c_regless = r.re2c_regless;
        this.re2c_subhist = r.re2c_subhist;
        this.re2c_tstring = r.re2c_tstring;
        this.re2c_autotags = r.re2c_autotags;
    }

    /**
     * Produce all the charts for the configured samples and the measurements, if any, and
     * otherwise executes them for the specified algorithms.
     *
     * @param      reTest array of algorithms
     * @param      mfile name of the measure file
     * @param      chart name of the chart file
     */

    private void bench(ReTdfa[] reTest){
        bench(reTest,MEA100,CHARTMEA);
    }
    private void bench(ReTdfa[] reTest, String mfile, String chart){
        // read the samples
        Samples samp = new Samples();
        samp.read(SAMPLES);
        String[][] res = samp.res;
        String[][][][] texts = samp.texts;

        // read the measures
        File mea = new File(mfile);
        System.out.printf("measures file %s\n",mfile);
        if (!mea.exists()){
            benchMeasure(reTest,mfile);
        }

        long[][][][] matrc = null;
        long[][][][] matrp = null;
        long[][][][] matrm = null;
        long[][][][] matrf = null;
        try {
            FileInputStream fileIn = new FileInputStream(mfile);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            matrc = (long[][][][])in.readObject();
            matrp = (long[][][][])in.readObject();
            matrm = (long[][][][])in.readObject();
            matrf = (long[][][][])in.readObject();
            in.close();
            fileIn.close();
        } catch(FileNotFoundException exc){
            System.out.printf(mfile + " not found\n");
            System.exit(1);
        } catch(IOException exc){
            exc.printStackTrace();
            System.out.printf("%s\n",exc);
            System.exit(1);
        } catch(ClassNotFoundException c){
            System.out.printf(mfile + " not found\n");
            System.exit(1);
        }
/*
for (int a = 0; a < reTest.length; a++){
    Trc.out.printf("algo %s\n",a);
    for (int i = 0; i < matrm.length; i++){
        for (int j = 0; j < matrm[i].length; j++){
            String str = "";
            for (int k = 0; k < matrm[i][j].length; k++){
                str += " " + matrm[i][j][k][a];
            }
            Trc.out.printf("%s.%s %s\n",i,j,str);
        }
    }
}
*/

        for (int a = 0; a < reTest.length; a++){
            double ptim = 0;
            for (int i = 0; i < matrp.length; i++){                 // visit REs buckets
                for (int j = 0; j < matrp[i].length; j++){          // for each re
                    for (int k = 0; k < matrp[i][j].length; k++){   // visit text buckets
                        if (matrp[i][j][k][a] < Long.MAX_VALUE-1){
                            ptim += matrp[i][j][k][a];
                        }
                    }
                }
            }
            double ctim = 0;
            for (int i = 0; i < matrc.length; i++){                 // visit REs buckets
                for (int j = 0; j < matrc[i].length; j++){          // for each re
                    for (int k = 0; k < matrc[i][j].length; k++){   // visit text buckets
                        if (matrc[i][j][k][a] < Long.MAX_VALUE-1){
                            ctim += matrc[i][j][k][a];
                        }
                    }
                }
            }
            System.out.printf("algo %s parse time %.0f sec, compilation time %.0f sec\n",
                reTest[a].name,ptim/1000000000,ctim/1000000000);
        }

        // produce charts
        try {
            html = new PrintStream(chart);
            System.out.printf("generating chart file %s\n",chart);
        } catch (FileNotFoundException exc){
            Trc.out.printf("charts measurements file error\n");
            System.exit(1);
        }
        html.printf("<!DOCTYPE html>\n");
        html.printf("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
        html.printf("<script>\n");
        try {
            BufferedReader in = new BufferedReader(new FileReader("chart.js"));
            for (;;){
                String line = in.readLine();
                if (line == null) break;
                html.printf("%s\n",line);
            }
            in.close();
        } catch (IOException exc){
            System.out.printf("error on file %s\n",exc);
            System.exit(1);
        }
        html.printf("</script>\n");
        html.printf("</head><body>\n");
        html.printf("<h2>Comparison of algorithm variants</h2>\n");

        String[] algolabels = new String[reTest.length];
        for (int i = 0; i < reTest.length; i++){
             algolabels[i] = reTest[i].name + "|" + colors[i];
        }

        int fact[] = new int[]{1,2,5, 10,20,50, 100,200,500, 1000};
        html.printf("<h3>Parse speed</h3>\n");
        speedVsReLength(matrp,texts,algolabels,fact,1);
        // speedVsTextLength(matrp,texts,algolabels,fact,2);
        html.printf("<h3>Compilation speed</h3>\n");
        speedCompVsReLength(matrc,res,algolabels,100);
        html.printf("<h3>FA size</h3>\n");
        faVsReLength(matrf,res,algolabels,110);
        html.printf("<h3>Compilation footprint</h3>\n");
        cfpVsReLength(matrf,res,algolabels,120);
        html.printf("<h3>Memory usage</h3>\n");
        memoryVsTextLength(matrm,texts,algolabels,fact,200);
        memoryVsReLength(matrm,texts,algolabels,fact,201);
        memoryAlgo(matrm,texts,algolabels,fact,300);

        html.printf("</body></html>\n");
        html.close();
    }

    /** The html file for the charts. */
    private static PrintStream html;

    /** The colors for the curves. */
    private static String[] colors = new String[]{
        "blue","violet","indigo","red","orange","black","limegreen","brown",
        "deeppink","slateblue","darkblue","green"};

    /** The list of values to be plotted in charts. */
    private static LinkedList<String[]> plot;

    /**
     * Produce a chart with the parse speed vs RE length.
     *
     * @param      matr matrix of measurements
     * @param      texts matrix of texts
     * @param      algoLabels name and color of algorithms
     * @param      fact vector telling the number of times texts are concatenated for each bucket
     * @param      nchart sequence number of the chart to produce
     */

    private void speedVsReLength(long[][][][] matr, String[][][][] texts, String[] algoLabels,
        int fact[], int nchart){
        // chart speed vs RE length
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        // sum up all times for a RE bucket
        for (int i = 0; i < matr.length; i++){
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((i+1)*10);
            for (int b = 0; b < algoLabels.length; b++){
                long tim = 0;
                long tok = 0;
                // visit the text buckets
                for (int k = 0; k < matr[0][0].length; k++){
                    long timb = 0;
                    long tokb = 0;
                    for (int j = 0; j < matr[i].length; j++){    // visit bucket of a RE
                        // visit the measures of a RE
                        long v = matr[i][j][k][b];
                        if (v == Long.MAX_VALUE-1){              // measure not done
                            tokb = 0;
                            continue;
                        }
                        timb += v;
                        for (int l = 0; l < texts[i][j][k].length; l++){
                            String s = texts[i][j][k][l];
                            tokb += s == null ? 0 : s.length();
                        }
                    }
                    if (tokb == 0) break;
                    tim += timb;
                    if (tim < 0) tim = Long.MAX_VALUE;
                    tok += tokb;
                }
                double val = 0;
                if (tim > 0) val = (double)tok/((double)tim/1000000.0);  // cycles to ms
                if (tok == 0) val = Double.NaN;
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = "Parse speed vs RE length, texts 0:1M";
        addChart(nchart,"RE length (characters)","characters/ms",xtitle,"Algorithm",true,0);
    }

    /**
     * Produce a chart with the parse speed vs text length.
     *
     * @param      matr matrix of measurements
     * @param      texts matrix of texts
     * @param      algoLabels labels of the algorithms
     * @param      fact vector telling the number of times texts are concatenated for each bucket
     * @param      nchart sequence number of the chart to produce
     */

    private void speedVsTextLength(long[][][][] matr, String[][][][] texts, String[] algoLabels,
        int fact[], int nchart){
        // sum up all times for a text bucket
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        for (int k = 0; k < 10; k++){                            // for each text bucket
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((k+1)*TEXT_SAMPLES_LENGTH);
            for (int b = 0; b < algoLabels.length; b++){
                long tim = 0;
                long tok = 0;
                for (int i = 0; i < matr.length; i++){
                    long timb = 0;
                    long tokb = 0;
                    for (int j = 0; j < matr[i].length; j++){    // visit bucket of a RE
                        long v = matr[i][j][k][b];
                        if (v == Long.MAX_VALUE-1){              // measure not done
                            tokb = 0;
                            continue;
                        }
                        timb += v;
                        if (timb < 0) timb = Long.MAX_VALUE;
                        for (int l = 0; l < texts[i][j][k].length; l++){
                            String s = texts[i][j][k][l];
                            tokb += s == null ? 0 : s.length();
                        }
                    }
                    if (tokb == 0) break;
                    tok += tokb;
                    tim += timb;
                    if (tim < 0) tim = Long.MAX_VALUE;
                }
                double val = 0;
                if (tim > 0) val = (double)tok/((double)tim/1000000.0); // cycles to ms
                if (tim == Long.MAX_VALUE) val = Double.NaN;
                if (tok == 0) val = Double.NaN;
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = "Parse speed vs text length, texts 0:1M";
        addChart(nchart,"Text length (characters)","characters/ms",xtitle,"Algorithm",false,0);
    }

    /**
     * Produce a chart with the compilation speed vs RE length.
     *
     * @param      matr matrix of measurements
     * @param      res matrix of REs
     * @param      algoLabels name and color of algorithms
     * @param      nchart sequence number of the chart to produce
     */

    private void speedCompVsReLength(long[][][][] matr, String[][] res, String[] algoLabels,
        int nchart){
        // chart speed vs RE length
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        // sum up all times for a RE bucket
        for (int i = 0; i < matr.length; i++){
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((i+1)*10);
            for (int b = 0; b < algoLabels.length; b++){
                long tim = 0;
                long tok = 0;
                // visit the RE bucket
                for (int j = 0; j < matr[i].length; j++){    // visit bucket of a RE
                    // visit the measures of a RE
                    long v = matr[i][j][0][b];
                    if (v == Long.MAX_VALUE-1){              // measure not done
                        continue;
                    }
                    tim += v;
                    if (tim < 0) tim = Long.MAX_VALUE;
                    tok += res[i][j].length();
                }
                double val = 0;
                if (tim > 0) val = (double)tok/((double)tim/1000000.0);  // cycles to ms
                if (tok == 0) val = Double.NaN;
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = "Parser-construction speed vs RE length";
        addChart(nchart,"RE length (characters)","characters/ms",xtitle,"Algorithm",true,0);
    }

    /**
     * Produce a chart with the FA size vs RE length.
     *
     * @param      matr matrix of measurements
     * @param      res matrix of REs
     * @param      algoLabels name and color of algorithms
     * @param      nchart sequence number of the chart to produce
     */

    private void faVsReLength(long[][][][] matr, String[][] res, String[] algoLabels,
        int nchart){
        compVsReLength(matr,res,algoLabels,nchart,true);
    }
    private void cfpVsReLength(long[][][][] matr, String[][] res, String[] algoLabels,
        int nchart){
        compVsReLength(matr,res,algoLabels,nchart,false);
    }

    private void compVsReLength(long[][][][] matr, String[][] res, String[] algoLabels,
        int nchart, boolean fa){
        // chart speed vs RE length
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        // sum up all times for a RE bucket
        for (int i = 0; i < matr.length; i++){
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((i+1)*10);
            for (int b = 0; b < algoLabels.length; b++){
                long max = 0;
                long tok = 0;
                // visit the RE bucket
                for (int j = 0; j < matr[i].length; j++){    // visit bucket of a RE
                    // visit the measures of a RE
                    long v = matr[i][j][fa ? 0 : 1][b];
                    if (v == Long.MAX_VALUE-1){              // measure not done
                        continue;
                    }
                    max += v;
                    tok += res[i][j].length();
                }
                double val = 0;
                if (tok == 0){
                    val = Double.NaN;
                } else {
                    val = max/tok;
                }
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = fa ? "FA size vs RE length" : "Compile footprint vs RE length";
        addChart(nchart,"RE length (characters)","bytes/chars",xtitle,"Algorithm",true,0);
    }

    /**
     * Produce a chart with the memory vs text length by algorithm.
     *
     * @param      matr matrix of measurements
     * @param      texts matrix of texts
     * @param      algoLabels labels of the algorithms
     * @param      fact vector telling the number of times texts are concatenated for each bucket
     * @param      nchart sequence number of the chart to produce
     */

    private void memoryAlgo(long[][][][] matr, String[][][][] texts,
        String[] algoLabels, int fact[], int nchart){
        // draw a chart for each algo, with text lengths in the x axis and curves for
        // increasing RE length
        String[] complLabels = new String[]{"0",
            "10|#000033","20|#000099","30|#0000FF","40|#009933","50|#009999",
            "60|#0099FF","70|#660000","80|#660066","90|#6600CC","100|#990000"};
        for (int b = 0; b < algoLabels.length; b++){
            plot = new LinkedList<String[]>();
            plot.add(complLabels);
            for (int k = 0; k < 10; k++){                // visit text buckets
                String[] plotEle = new String[complLabels.length];
                plot.add(plotEle);
                plotEle[0] = "" + ((k+1)*TEXT_SAMPLES_LENGTH);
                for (int i = 0; i < matr.length; i++){   // visit all its REs buckets
                    long mem = 0;
                    long tok = 0;
                    for (int j = 0; j < matr[i].length; j++){    // visit bucket of a RE
                        long v = matr[i][j][k][b];
                        if (v == Long.MAX_VALUE-1){                  // measure not done
                            tok = 0;
                            break;
                        }
                        mem += v;
                        for (int l = 0; l < texts[i][j][k].length; l++){
                            String s = texts[i][j][k][l];
                            tok += s == null ? 0 : s.length();
                        }
                    }
                    double val = 0;
                    if (mem > 0) val = (double)mem/(double)tok;
                    if (tok == 0) val = Double.NaN;
                    plotEle[i+1] = String.format("%.2f",val);
                }
            }
            String algoname = algoLabels[b].substring(0,algoLabels[b].indexOf("|"));
            String xtitle = algoname + " memory vs text length, texts by RE length ";
            xtitle += "0:1000";
            addChart(b+nchart,"Text length (characters)","bytes/char",xtitle,"RE length",false,b);
        }
    }

    /**
     * Produce a chart with the memory vs text length.
     *
     * @param      matr matrix of measurements
     * @param      texts matrix of texts
     * @param      algoLabels labels of the algorithms
     * @param      fact vector telling the number of times texts are concatenated for each bucket
     * @param      nchart sequence number of the chart to produce
     */

    private void memoryVsTextLength(long[][][][] matr, String[][][][] texts,
        String[] algoLabels, int fact[], int nchart){
        // sum up all values for a text bucket
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        for (int k = 0; k < 10; k++){                  // for each text bucket
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((k+1)*TEXT_SAMPLES_LENGTH);
            for (int b = 0; b < algoLabels.length; b++){
                long fpave = 0;
                long fpnr = 0;
                for (int i = 0; i < matr.length; i++){
                    for (int j = 0; j < matr[i].length; j++){   // visit bucket of a RE
                        long v = matr[i][j][k][b];
                        if (v == Long.MAX_VALUE-1){             // measure not done
                            continue;
                        }
                        fpave += v;
                        fpnr++;
                    }
                }
                double val = 0;
                val = fpnr > 0 ? fpave/fpnr : Double.NaN;
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = "Memory vs text length, texts ";
        xtitle += "0:1000";
        addChart(nchart,"Text length (characters)","bytes/char",xtitle,"Algorithm",false,0);
    }

    /**
     * Produce a chart with the memory vs RE length.
     *
     * @param      matr matrix of measurements
     * @param      texts matrix of texts
     * @param      algoLabels labels of the algorithms
     * @param      fact vector telling the number of times texts are concatenated for each bucket
     * @param      nchart sequence number of the chart to produce
     */

    private void memoryVsReLength(long[][][][] matr, String[][][][] texts,
        String[] algoLabels, int fact[], int nchart){
        // sum up all times for a RE bucket
        plot = new LinkedList<String[]>();
        String[] labels = new String[algoLabels.length+1];
        labels[0] = "0";
        System.arraycopy(algoLabels,0,labels,1,algoLabels.length);
        plot.add(labels);
        for (int i = 0; i < matr.length; i++){                  // for each RE bucket
            String[] plotEle = new String[labels.length];
            plot.add(plotEle);
            plotEle[0] = "" + ((i+1)*10);
            for (int b = 0; b < algoLabels.length; b++){
                long fpave = 0;
                long fpnr = 0;
                // visit the RE bucket
                for (int k = 0; k < matr[0][0].length; k++){
                    for (int j = 0; j < matr[i].length; j++){   // visit bucket of a RE
                        // visit the measures of a RE
                        long v = matr[i][j][k][b];
                        if (v == Long.MAX_VALUE-1){             // measure not done
                            continue;
                        }
                        fpave += v;
                        fpnr++;
                    }
                }
                double val = 0;
                val = fpnr > 0 ? fpave/fpnr : Double.NaN;
                plotEle[b+1] = String.format("%.2f",val);
            }
        }
        String xtitle = "Memory vs RE length, texts ";
        xtitle += "0:1000";
        addChart(nchart,"RE length (characters)","bytes/char",xtitle,"Algorithm",false,0);
    }

    /** The sequence number of the chart to produce. */
    private static int chartNr;

    /**
     * Add a chart to the html file using the plot data.
     *
     * @param      t sequence number of the chart to produce
     * @param      xlabel label of the x-axis
     * @param      ylabel label of the y-axis
     * @param      title title of the chart
     * @param      curvesLegend legend of the curves
     * @param      xlinear <code>true</code> if x-axis linear, <code>false</code> if logarithmic
     * @param      algo number of the algorithm if chart an algorithm, 0 otherwise
     */

    private static void addChart(int t, String xlabel, String ylabel, String title,
        String curvesLegend, boolean xlinear, int algo){
        html.printf("<h3>Chart %s</h3>\n",chartNr++);
        html.printf("<p><div style=\"border:1px solid;width:1000px;\">\n");
        html.printf("<svg id=diag%s xmlns=\"http://www.w3.org/2000/svg\" " +
            "xmlns:xlink=\"http://www.w3.org/1999/xlink\" " + 
            "svg width=1000 height=380>\n<script>\n",t);
        html.printf("xAxisName = \"" + xlabel + "\";yAxisName = \"" + ylabel + "\";\n");
        if (curvesLegend != null){
            html.printf("curvesLegend = \"" + curvesLegend + "\";\n");
        }
        html.printf("svgChart(\"diag%s\",\"%s\",\"%s\",[\n",t,title,"");
        for (int i = 0; i < plot.get(0).length; i++){
            html.printf("[");
            boolean first = true;
            for (int j = 0; j < plot.size(); j++){
                String[] ele = plot.get(j);
                if (ele[i] != null && ele[i].length() > 0){
                    if (!first) html.printf(",");
                    first = false;
                    if (i == 0 || j == 0){
                        html.printf("\"%s\"",ele[i]);
                    } else {
                        html.printf("%s",ele[i]);
                    }
                }
            }
            if (i < plot.get(0).length-1){
                html.printf("],\n");
            } else {
                html.printf("]\n");
            }
        }
        html.printf("])\n</script>\n</svg>\n</div>\n");
    }

    /**
     * Run all the verification tests.
     */

    private void test(){
//        ckshow = true;

        feature("Tstring trie");
        TstringTrie tr = new TstringTrie(2,16);
        int prev = 0;
        prev = testtrieappend(0,"abc","abc",tr,0);
        prev = testtrieappend(1,"def","abcdef",tr,prev);
//tr.trace();
        prev = testtrieappend(2,"hg","abcdefhg",tr,prev);
        prev = testtrieappend(3,"qqqqqqq","abcdefhgqqqqqqq",tr,prev);
        prev = testtrieappend(4,"aaa","abcdefhgqqqqqqqaaa",tr,prev);
//settrc("x");
//settrc("");
//tr.trace();
        // ast
        feature("ast");
        testAst(1,"","\u03b5");
        testAst(2,"a","a");
        testAst(3,"a b","ab");
        testAst(4,"a b c","abc");
        testAst(5,"a|b","a|b");
        testAst(6,"a|b|c","a|b|c");
        testAst(7,"(a)","(a)");
        testAst(8,"(a)*","(a)*");
        testAst(9,"(a)+","(a)+");
        testAst(10,"(a b)","(ab)");
        testAst(11,"(a|b)","(a|b)");
        testAst(12,"(a (b))","(a(b))");
        testAst(13,"(a)?","(a)?");
        testAst(14,"((a))","((a))");
        testAst(15,"a (b) c","a(b)c");
        testAst(16,"a (b*) c","a((b)*)c");
        testAst(17,"ab|c","ab|c");
        testAst(18,"a*","(a)*");
        testAst(19,"a+","(a)+");
        testAst(20,"a?","(a)?");
        testAst(21,"a{2}","(a){2}");
        testAst(22,"a{2,}","(a){2,}");
        testAst(23,"a{2,4}","(a){2,4}");
        testAst(24,"(a){2}","(a){2}");
        testAst(25,"(a){2,}","(a){2,}");
        testAst(26,"(a){2,4}","(a){2,4}");
        testAst(27,"a*(b|\u03b5)","(a)*(b|\u03b5)");
        testAst(28,"a{0,}","(a)*");
        testAst(29,"a{1,}","(a)+");
        testAst(30,".",".");
        testAst(31,"[ab]","[ab]");
        testAst(32,"[abd]","[abd]");
        testAst(33,"[a-d]","[a-d]");
        testAst(34,"[^a-dg-p]","[^a-dg-p]");

        testAst(100,"()","(\u03b5)");
        testAst(101,"|","\u03b5|\u03b5");
        testAst(102,"a|","a|\u03b5");
        testAst(103,"()*","(\u03b5)*");
        testAst(104,"()?","(\u03b5)?");

        testAst(200,"(","error");
        testAst(201,"(a","error");
        testAst(202,"a{0}","error");
        testAst(203,"a{3,2}","error");
        testAst(204,"[","error");
        testAst(205,"[a","error");
        testAst(206,"[^","error");
        testAst(207,"[a-","error");
        testAst(208,"[a-b","error");

        feature("Ast groups");
        this.astGroups = AST_GROUPS_ONE;
        testAstTree(0,"a","<a[0,0]>");
        testAstTree(1,"a|b","<|[0,0]<a[0,0]>,<b[0,0]>>");
        testAstTree(2,"ab","<∙[0,0]<a[0,0]>,<b[0,0]>>");
        testAstTree(3,"a*","<*[0,0]<a[0,0]>>");
        testAstTree(4,"(a)","<()[1,1]<a[0,0]>>");
        testAstTree(5,"(a)*","<()*[1,1]<a[0,0]>>");
        testAstTree(6,"a(b)","<∙[1,0]<a[2,0]>,<()[3,1]<b[0,0]>>>");
        testAstTree(7,"a(b*)","<∙[1,0]<a[2,0]>,<()[3,1]<*[0,0]<b[0,0]>>>>");

        this.astGroups = AST_GROUPS_FOLDED;
        testAstTree(10,"a","<a[1,1]>");
        testAstTree(11,"a|b","<|[1,1]<a[0,0]>,<b[0,0]>>");
        testAstTree(12,"ab","<∙[1,1]<a[0,0]>,<b[0,0]>>");
        testAstTree(13,"a*","<()*[1,1]<a[0,0]>>");
        testAstTree(14,"(a)","<a[1,2]>");
        testAstTree(15,"(a)*","<()*[1,1]<a[2,1]>>");
        testAstTree(16,"a(b)","<∙[1,1]<a[2,0]>,<b[3,1]>>");
        testAstTree(17,"a(b*)","<∙[1,1]<a[2,0]>,<()*[3,1]<b[0,0]>>>");

        this.astGroups = AST_GROUPS_SEP;
        testAstTree(20,"a","<()[1,1]<a[0,0]>>");
        testAstTree(21,"a|b","<()[1,1]<|[0,0]<a[0,0]>,<b[0,0]>>>");
        testAstTree(22,"ab","<()[1,1]<∙[0,0]<a[0,0]>,<b[0,0]>>>");
        testAstTree(23,"a*","<()[1,1]<*[0,0]<a[0,0]>>>");
        testAstTree(24,"(a)","<()[1,1]<()[2,2]<a[0,0]>>>");
        testAstTree(25,"(a)*","<()[1,1]<*[2,0]<()[3,2]<a[0,0]>>>>");
        testAstTree(26,"a(b)","<()[1,1]<∙[2,0]<a[3,0]>,<()[4,2]<b[0,0]>>>>");
        testAstTree(27,"a(b*)","<()[1,1]<∙[2,0]<a[3,0]>,<()[4,2]<*[0,0]<b[0,0]>>>>>");

        this.astGroups = AST_GROUPS_GRO1;
        testAstTree(30,"a","<a[0,0]>");
        testAstTree(31,"a|b","<|[0,0]<a[0,0]>,<b[0,0]>>");
        testAstTree(32,"ab","<∙[0,0]<a[0,0]>,<b[0,0]>>");
        testAstTree(33,"a*","<*[0,0]<a[0,0]>>");
        testAstTree(34,"(a)","<(){}[1,0]<a[2,1]>>");
        testAstTree(35,"(a)*","<()*[1,0]<a[2,1]>>");
        testAstTree(36,"a(b)","<∙[1,0]<a[2,0]>,<(){}[3,0]<b[4,1]>>>");
        testAstTree(37,"a(b*)","<∙[1,0]<a[2,0]>,<(){}[3,0]<*[4,1]<b[0,0]>>>>");
        this.astGroups = AST_GROUPS_ONE;

        feature("TNFA");
        this.posix = false;
        // tagged (implicitly then finreg)
        testTNFA(1,"","0:t1->3; 3:t2->1; 1f:");
        testTNFA(2,"a","0:t1->2; 2:a->3; 3:t2->1; 1f:");
        testTNFA(3,"ab","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t5->7; 7:b->8; 8:t6->3; 3:t2->1; 1f:");
        testTNFA(4,"a|b","0:t1->2; 2:p0->4,p1->7; 4:t3->5; 7:t5->8; 5:a->6; 8:b->9; 6:t4->3; 9:t6->3; 3:t2->1; 1f:");
        testTNFA(5,"a|b|c","0:t1->2; 2:p0->4,p1->10; 4:t3->5; 10:p0->7,p1->11; 5:a->6; 7:t5->8; 11:t7->12; 6:t4->3; 8:b->9; 12:c->13; 3:t2->1; 9:t6->3; 13:t8->3; 1f:");
        testTNFA(6,"a*","0:t1->2; 2:p0->4,p1->3; 4:t3->6; 3:t2->1; 6:a->7; 1f:; 7:t4->5; 5:p1->3,p0->4");
        testTNFA(7,"a+","0:t1->4; 4:t3->6; 6:a->7; 7:t4->5; 5:p0->4,p1->3; 3:t2->1; 1f:");
        testTNFA(8,"a?","0:t1->2; 2:p0->4,p1->3; 4:t3->6; 3:t2->1; 6:a->7; 1f:; 7:t4->3");
        testTNFA(9,"a{2}","0:t1->2; 2:t3->7; 7:a->8; 8:t4->6; 6:t3->9; 9:a->10; 10:t4->3; 3:t2->1; 1f:");
        testTNFA(10,"a{2,}","0:t1->2; 2:t3->7; 7:a->8; 8:t4->9; 9:t3->11; 11:a->12; 12:t4->10; 10:p1->3,p0->9; 3:t2->1; 1f:");
        testTNFA(11,"a{2,4}","0:t1->2; 2:t3->7; 7:a->8; 8:t4->6; 6:t3->10; 10:a->11; 11:t4->9; 9:p0->12,p1->3; 12:t3->14; 3:t2->1; 14:a->15; 1f:; 15:t4->13; 13:p0->16,p1->3; 16:t3->18; 18:a->19; 19:t4->3");
        testTNFA(12,"a{0,2}","0:t1->2; 2:p0->6,p1->3; 6:t3->8; 3:t2->1; 8:a->9; 1f:; 9:t4->7; 7:p0->10,p1->3; 10:t3->12; 12:a->13; 13:t4->3");
        testTNFA(13,".","0:t1->2; 2:.->3; 3:t2->1; 1f:");
        testTNFA(14,"[ab]","0:t1->2; 2:[ab]->3; 3:t2->1; 1f:");
        testTNFA(15,"[abd]","0:t1->2; 2:[abd]->3; 3:t2->1; 1f:");
        testTNFA(16,"[a-d]","0:t1->2; 2:[a-d]->3; 3:t2->1; 1f:");
        testTNFA(17,"[^a-dg-p]","0:t1->2; 2:[^a-dg-p]->3; 3:t2->1; 1f:");
        this.posix = true;
        this.negtags = true;
        this.okui = true;
this.tagless = true;
this.finreg = false;
        testTNFA(21,"","0:t1->3; 3:t2->1; 1f:");
        testTNFA(22,"a","0:t1->2; 2:a->3; 3:t2->1; 1f:");
        testTNFA(23,"ab","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t5->7; 7:b->8; 8:t6->3; 3:t2->1; 1f:");
        testTNFA(24,"a|b","0:t1->1,t1->2; 1:t3->3; 2:t-3->4; 3:a->5; 4:t5->6; 5:t4->7; 6:b->8; 7:t2->9; 8:t6->7; 9f:");
        testTNFA(25,"a|b|c","0:t1->1,t1->2,t1->3; 1:t3->4; 2:t-3->5; 3:t-3->6; 4:a->7; 5:t5->8; 6:t-5->9; 7:t4->10; 8:b->11; 9:t7->12; 10:t2->13; 11:t6->10; 12:c->14; 13f:; 14:t8->10");
        testTNFA(26,"a*","0:t1->1,t1->2; 1:t3->3; 2:t-3->4; 3:a->5; 4:t2->6; 5:t4->1,t4->4; 6f:");
        testTNFA(27,"a+","0:t1->1; 1:t3->2; 2:a->3; 3:t4->1,t4->4; 4:t2->5; 5f:");
        testTNFA(28,"a?","0:t1->1,t1->2; 1:t3->3; 2:t-3->4; 3:a->5; 4:t2->6; 5:t4->4; 6f:");
        testTNFA(29,"a{2}","0:t1->2; 2:t3->7; 7:a->8; 8:t4->6; 6:t3->9; 9:a->10; 10:t4->3; 3:t2->1; 1f:");
        testTNFA(30,"a{2,}","0:t1->1; 1:t3->2; 2:a->3; 3:t4->4; 4:t3->5; 5:a->6; 6:t4->7,t4->4; 7:t2->8; 8f:");
        testTNFA(31,"a{2,4}","0:t1->1; 1:t3->2; 2:a->3; 3:t4->4; 4:t3->5; 5:a->6; 6:t4->7,t4->8; 7:t2->9; 8:t3->10; 9f:; 10:a->11; 11:t4->7,t4->12; 12:t3->13; 13:a->14; 14:t4->7");
        testTNFA(32,"a{0,2}","0:t1->1,t1->2; 1:t3->3; 2:t-3->4; 3:a->5; 4:t2->6; 5:t4->4,t4->7; 6f:; 7:t3->8; 8:a->9; 9:t4->4");
        testTNFA(33,".","0:t1->2; 2:.->3; 3:t2->1; 1f:");
        testTNFA(34,"[ab]","0:t1->2; 2:[ab]->3; 3:t2->1; 1f:");
        testTNFA(35,"[abd]","0:t1->2; 2:[abd]->3; 3:t2->1; 1f:");
        testTNFA(36,"[a-d]","0:t1->2; 2:[a-d]->3; 3:t2->1; 1f:");
        testTNFA(37,"[^a-dg-p]","0:t1->2; 2:[^a-dg-p]->3; 3:t2->1; 1f:");
        testTNFA(38,"((h(b)|h)z)*","0:t1->1,t1->2; 1:t3->3; 2:t-3->4; 3:t5->5; 4:t2->6; 5:t7->7,t7->8; 6f:; 7:t9->9; 8:t-9->10; 9:t11->11; 10:t17->12; 11:h->13; 12:h->14; 13:t12->15; 14:t18->16; 15:t13->17; 16:t8->18; 17:t15->19; 18:t6->20; 19:b->21; 20:t19->22; 21:t16->23; 22:z->24; 23:t14->25; 24:t20->26; 25:t10->16; 26:t4->1,t4->4");

        this.astGroups = AST_GROUPS_GRO1;
        this.autotags = false;

        testTNFA(41,"","0:->1; 1f:");
        testTNFA(42,"a","0:a->1; 1f:");
        testTNFA(43,"ab","0:a->2; 2:b->1; 1f:");
        testTNFA(44,"a|b","0:->2,->3; 2:a->1; 3:b->1; 1f:");
        testTNFA(45,"a?","0:->2,->1; 2:a->1; 1f:");
        testTNFA(46,"a*","0:->2,->1; 2:a->3; 1f:; 3:->1,->2");
        testTNFA(47,"a+","0:a->2; 2:->1,->0; 1f:");
        testTNFA(48,"a{2}","0:a->2; 2:a->1; 1f:");
        testTNFA(49,"a{2,}","0:a->2; 2:a->3; 3:->1,->2; 1f:");
        testTNFA(50,"a{2,4}","0:a->2; 2:a->3; 3:->1,->4; 1f:; 4:a->5; 5:->1,->6; 6:a->1");
        testTNFA(51,"a{0,4}","0:->2,->1; 2:a->3; 1f:; 3:->1,->4; 4:a->5; 5:->1,->6; 6:a->7; 7:->1,->8; 8:a->1");
        testTNFA(52,"(a)","0:t1->2; 2:t3->4; 4:a->5; 5:t4->3; 3:t2->1; 1f:");
        testTNFA(53,"(ab)","0:t1->2; 2:t3->4; 4:a->6; 6:b->5; 5:t4->3; 3:t2->1; 1f:");
        testTNFA(54,"a(b)","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t5->7; 7:t7->9; 9:b->10; 10:t8->8; 8:t6->3; 3:t2->1; 1f::");
        testTNFA(55,"a|(b)","0:t1->2; 2:->4,->7; 4:t3->5; 7:t-3->8; 5:a->6; 8:t5->9; 6:t4->3; 9:t7->11; 3:t2->1; 11:b->12; 1f:; 12:t8->10; 10:t6->3");
        testTNFA(56,"(a|b)","0:t1->2; 2:t3->4; 4:->6,->7; 6:a->5; 7:b->5; 5:t4->3; 3:t2->1; 1f:");
        testTNFA(57,"(a)?","0:t1->2; 2:->4,t-3->3; 4:t3->5; 3:t2->1; 5:a->6; 1f:; 6:t4->3");
        testTNFA(58,"(a)*","0:t1->2; 2:->4,t-3->3; 4:t3->6; 3:t2->1; 6:a->7; 1f:; 7:t4->5; 5:->3,->4");
        testTNFA(59,"(a)+","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:->3,->2; 3:t2->1; 1f:");
        testTNFA(60,"(a){2}","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t3->7; 7:a->8; 8:t4->3; 3:t2->1; 1f:");
        testTNFA(61,"(a){2,}","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t3->8; 8:a->9; 9:t4->7; 7:->3,->4; 3:t2->1; 1f:");
        testTNFA(62,"(a){2,4}","0:t1->2; 2:t3->5; 5:a->6; 6:t4->4; 4:t3->8; 8:a->9; 9:t4->7; 7:->3,->10; 3:t2->1; 10:t3->12; 1f:; 12:a->13; 13:t4->11; 11:->3,->14; 14:t3->15; 15:a->16; 16:t4->3");
        testTNFA(63,"(a){0,4}","0:t1->2; 2:->4,t-3->3; 4:t3->6; 3:t2->1; 6:a->7; 1f:; 7:t4->5; 5:->3,->8; 8:t3->10; 10:a->11; 11:t4->9; 9:->3,->12; 12:t3->14; 14:a->15; 15:t4->13; 13:->3,->16; 16:t3->17; 17:a->18; 18:t4->3");
        testTNFA(64,"a|b(c)","0:t1->2; 2:->4,->7; 4:t3->5; 7:t-3->8; 5:a->6; 8:t5->9; 6:t4->3; 9:t7->12; 3:t2->1; 12:b->13; 1f:; 13:t8->11; 11:t9->14; 14:t11->16; 16:c->17; 17:t12->15; 15:t10->10; 10:t6->3");
        this.astGroups = AST_GROUPS_ALL;
        this.autotags = true;

//        ckshow=true;
        this.negtags = true;
        // tree
        feature("tree");
//ckshow = false;
//ckshow = true;
        this.astGroups = AST_GROUPS_GRO1;
//this.treeTrace = "okui-incr-tless-posix";
//settrc("t");
        testTree(300,"a","a","(∧a∧)∧⊣$",null,"a⊣$");
//settrc("");
//this.treeTrace = "";
        testTree(301,"aa","aa","(∧(1a1)1(2a2)2)∧⊣$",null,"aa⊣$");
//settrc("t");
//settrc("");
        testTree(302,"a|b","a","(∧(1a1)1)∧⊣$",null,"a⊣$");
        testTree(303,"a|b","b","(∧(2b2)2)∧⊣$",null,"b⊣$");
//settrc("mk");
        testTree(304,"(a)*","","(∧)∧⊣$");
//settrc("");
        testTree(305,"(a)*","a","(∧(1a1)1)∧⊣$");
        testTree(306,"(a)*","aa","(∧(1a1)1(1a1)1)∧⊣$");
        testTree(307,"(a)+","a","(∧(1a1)1)∧⊣$");
        testTree(308,"(a)+","aa","(∧(1a1)1(1a1)1)∧⊣$");
        testTree(309,"(a)","a","(∧(1a1)1)∧⊣$");
        testTree(310,"(a)?","","(∧)∧⊣$");
        testTree(311,"(a)?","a","(∧(1a1)1)∧⊣$");
        testTree(312,"(a)*b","b","(∧(1)1(2b2)2)∧⊣$");
        testTree(313,"(a)*b","ab","(∧(1(1.1a1.1)1.1)1(2b2)2)∧⊣$");
        testTree(314,"aaab|aaac","aaac","(∧(2(2.1a2.1)2.1(2.2a2.2)2.2(2.3a2.3)2.3(2.4c2.4)2.4)2)∧⊣$",null,"aaac⊣$");
//this.treeTrace = "";
//settrc("");
        testTree(315,"(ab|(a)*)*","aba","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2)1.1)1(1(1.2(1.2.1a1.2.1)1.2.1)1.2)1)∧⊣$",null,"(∧(1(1.1ab)1.1)1(1(1.2(1.2.1a1.2.1)1.2.1)1.2)1)∧⊣$");
        testTree(316,"(a)?(ab)?","ab","(∧(1)1(2(2.1(2.1.1a2.1.1)2.1.1(2.1.2b2.1.2)2.1.2)2.1)2)∧⊣$",null,"(∧(1)1(2(2.1ab)2.1)2)∧⊣$");
        testTree(317,"(a)?((ab)?)(b)?","ab","(∧(1(1.1a1.1)1.1)1(2(2.1)2.1)2(3(3.1b3.1)3.1)3)∧⊣$");
        testTree(3171,"((a)?)(((ab)?)((b)?))","ab","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(2(2.1(2.1.1(2.1.1.1)2.1.1.1)2.1.1(2.1.2(2.1.2.1(2.1.2.1.1b2.1.2.1.1)2.1.2.1.1)2.1.2.1)2.1.2)2.1)2)∧⊣$");
//settrc("vt");
//settrc("");
        testTree(318,"((a)?((ab)?))(b)?","ab","(∧(1(1.1(1.1.1)1.1.1(1.1.2(1.1.2.1(1.1.2.1.1(1.1.2.1.1.1a1.1.2.1.1.1)1.1.2.1.1.1(1.1.2.1.1.2b1.1.2.1.1.2)1.1.2.1.1.2)1.1.2.1.1)1.1.2.1)1.1.2)1.1)1(2)2)∧⊣$",
            "(∧(1(1.1(1.1.1(1.1.1.1a1.1.1.1)1.1.1.1)1.1.1(1.1.2(1.1.2.1)1.1.2.1)1.1.2)1.1)1(2(2.1b2.1)2.1)2)∧⊣$",
            "(∧(1(1.1(1.1.1)1.1.1(1.1.2(1.1.2.1(1.1.2.1.1ab)1.1.2.1.1)1.1.2.1)1.1.2)1.1)1(2)2)∧⊣$");
        testTree(319,"(a)?(((ab)?)(b)?)","ab","(∧(1(1.1a1.1)1.1)1(2(2.1(2.1.1(2.1.1.1)2.1.1.1)2.1.1(2.1.2(2.1.2.1b2.1.2.1)2.1.2.1)2.1.2)2.1)2)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(2(2.1(2.1.1(2.1.1.1)2.1.1.1)2.1.1(2.1.2(2.1.2.1b2.1.2.1)2.1.2.1)2.1.2)2.1)2)∧⊣$");
        testTree(320,"(a)?(a)?","a","(∧(1(1.1a1.1)1.1)1(2)2)∧⊣$");
        testTree(321,"((a)?(a)?)((a)?(a)?)","aaa","(∧(1(1.1(1.1.1(1.1.1.1a1.1.1.1)1.1.1.1)1.1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1)1.1.2)1.1)1(2(2.1(2.1.1(2.1.1.1a2.1.1.1)2.1.1.1)2.1.1(2.1.2)2.1.2)2.1)2)∧⊣$");
        testTree(322,"((a)?(a)?)((a)?(a)?)((a)?(a)?)","aaa","(∧(1(1.1(1.1.1(1.1.1.1a1.1.1.1)1.1.1.1)1.1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1)1.1.2)1.1)1(2(2.1(2.1.1(2.1.1.1a2.1.1.1)2.1.1.1)2.1.1(2.1.2)2.1.2)2.1)2(3(3.1(3.1.1)3.1.1(3.1.2)3.1.2)3.1)3)∧⊣$");
        testTree(323,"((a)?(a)?)*","aaa","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.2(1.2.1a1.2.1)1.2.1)1.2)1(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.2)1.2)1)∧⊣$");
        testTree(324,"(a)?((ab)?)(b)?","ab","(∧(1(1.1a1.1)1.1)1(2(2.1)2.1)2(3(3.1b3.1)3.1)3)∧⊣$");
        testTree(325,"(ab)?((b)?a)","aba","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2)1.1)1(2(2.1(2.1.1)2.1.1(2.1.2a2.1.2)2.1.2)2.1)2)∧⊣$",
            null,"(∧(1(1.1ab)1.1)1(2(2.1(2.1.1)2.1.1(2.1.2a2.1.2)2.1.2)2.1)2)∧⊣$");
        testTree(326,"(a|ab|ba)*","aba","(∧(1(1.2(1.2.1a1.2.1)1.2.1(1.2.2b1.2.2)1.2.2)1.2)1(1(1.1a1.1)1.1)1)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(1(1.3(1.3.1b1.3.1)1.3.1(1.3.2a1.3.2)1.3.2)1.3)1)∧⊣$",
            "(∧(1ab)1(1a)1)∧⊣$");
        testTree(327,"(aba|a*b)(aba|a*b)","ababa","(∧(1(1.1(1.1.2(1.1.2.1(1.1.2.1.1a1.1.2.1.1)1.1.2.1.1)1.1.2.1(1.1.2.2b1.1.2.2)1.1.2.2)1.1.2)1.1)1(2(2.1(2.1.1(2.1.1.1a2.1.1.1)2.1.1.1(2.1.1.2b2.1.1.2)2.1.1.2(2.1.1.3a2.1.1.3)2.1.1.3)2.1.1)2.1)2)∧⊣$",
            null,"(∧(1(1.1ab)1.1)1(2(2.1aba)2.1)2)∧⊣$");
        testTree(328,"(aba|a*b)*","ababa","(∧(1(1.2(1.2.1(1.2.1.1a1.2.1.1)1.2.1.1)1.2.1(1.2.2b1.2.2)1.2.2)1.2)1(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2(1.1.3a1.1.3)1.1.3)1.1)1)∧⊣$",
            null,"(∧(1ab)1(1aba)1)∧⊣$");
        testTree(329,"(aba|ab|a)(aba|ab|a)","ababa","(∧(1(1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1(1.1.2.2b1.1.2.2)1.1.2.2)1.1.2)1.1)1(2(2.1(2.1.1(2.1.1.1a2.1.1.1)2.1.1.1(2.1.1.2b2.1.1.2)2.1.1.2(2.1.1.3a2.1.1.3)2.1.1.3)2.1.1)2.1)2)∧⊣$",
            null,"(∧(1(1.1ab)1.1)1(2(2.1aba)2.1)2)∧⊣$");
        testTree(330,"(aba|ab|a)*","ababa","(∧(1(1.2(1.2.1a1.2.1)1.2.1(1.2.2b1.2.2)1.2.2)1.2)1(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2(1.1.3a1.1.3)1.1.3)1.1)1)∧⊣$",
            null,"(∧(1ab)1(1aba)1)∧⊣$");
        testTree(331,"(a(b)?)(a(b)?)","aba","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2(1.1.2.1b1.1.2.1)1.1.2.1)1.1.2)1.1)1(2(2.1(2.1.1a2.1.1)2.1.1(2.1.2)2.1.2)2.1)2)∧⊣$");
        testTree(332,"(a(b)?)+","aba","(∧(1(1.1a1.1)1.1(1.2(1.2.1b1.2.1)1.2.1)1.2)1(1(1.1a1.1)1.1(1.2)1.2)1)∧⊣$");
        testTree(333,"(a*)(a*)","aa","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1)1(2(2.1)2.1)2)∧⊣$",
            null,"(∧(1(1.1aa)1.1)1(2(2.1)2.1)2)∧⊣$");
        testTree(334,"a*(a*)","aa","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1(2(2.1)2.1)2)∧⊣$",null,"(∧(1aa)1(2(2.1)2.1)2)∧⊣$");
        testTree(335,"(aa(b(b))?)+","aabbaa","(∧(1(1.1a1.1)1.1(1.2a1.2)1.2(1.3(1.3.1(1.3.1.1b1.3.1.1)1.3.1.1(1.3.1.2(1.3.1.2.1b1.3.1.2.1)1.3.1.2.1)1.3.1.2)1.3.1)1.3)1(1(1.1a1.1)1.1(1.2a1.2)1.2(1.3)1.3)1)∧⊣$");
        testTree(336,"(a(b)?)+","aba","(∧(1(1.1a1.1)1.1(1.2(1.2.1b1.2.1)1.2.1)1.2)1(1(1.1a1.1)1.1(1.2)1.2)1)∧⊣$");
        testTree(337,"(a)?b","b","(∧(1)1(2b2)2)∧⊣$");
        testTree(338,"a*b*","a","(∧(1(1.1a1.1)1.1)1(2)2)∧⊣$",null,"a⊣$");
        testTree(400,"","","(∧)∧⊣$",null,"⊣$");
        testTree(401,"()","","(∧(1)1)∧⊣$");
        testTree(402,"()*","","(∧(1)1)∧⊣$");
        testTree(403,"()+","","(∧(1)1)∧⊣$");
        testTree(404,"()?","","(∧(1)1)∧⊣$");
        testTree(405,"a*a*","","(∧(1)1(2)2)∧⊣$",null,"⊣$");
        testTree(406,".","a","(∧a∧)∧⊣$",null,"a⊣$");
        testTree(407,"[ab]","b","(∧b∧)∧⊣$",null,"b⊣$");
        testTree(408,"[abd]","b","(∧b∧)∧⊣$",null,"b⊣$");
        testTree(409,"[a-d]","b","(∧b∧)∧⊣$",null,"b⊣$");
        testTree(410,"[^a-dg-p]","e","(∧e∧)∧⊣$",null,"e⊣$");
        testTree(411,".a.","aaa","(∧(1a1)1(2a2)2(3a3)3)∧⊣$",null,"aaa⊣$");
        testTree(412,"((a)*)*","","(∧(1)1)∧⊣$");
        testTree(413,"(a|b)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$",null,"(∧(1a)1)∧⊣$");
        testTree(414,"(a|aa)*","aaa","(∧(1(1.2(1.2.1a1.2.1)1.2.1(1.2.2a1.2.2)1.2.2)1.2)1(1(1.1a1.1)1.1)1)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(1(1.1a1.1)1.1)1(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(415,"((a)?)","","(∧(1)1)∧⊣$");
        testTree(416,"((ab)?)","","(∧(1)1)∧⊣$");
        // ambiguous
        testTree(500,"((a)*)*","aa","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1)∧⊣$");
        testTree(501,"(a|b|ab)*","ab","(∧(1(1.3(1.3.1a1.3.1)1.3.1(1.3.2b1.3.2)1.3.2)1.3)1)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(1(1.2b1.2)1.2)1)∧⊣$");
        testTree(502,"(ab|a|b)*","abab","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2)1.1)1(1(1.1(1.1.1a1.1.1)1.1.1(1.1.2b1.1.2)1.1.2)1.1)1)∧⊣$",
            null,"(∧(1ab)1(1ab)1)∧⊣$");
        testTree(503,"(a|ab)(bc|c)","abc","(∧(1(1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1(1.1.2.2b1.1.2.2)1.1.2.2)1.1.2)1.1)1(2(2.1(2.1.2c2.1.2)2.1.2)2.1)2)∧⊣$",
            "(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(2(2.1(2.1.1(2.1.1.1b2.1.1.1)2.1.1.1(2.1.1.2c2.1.1.2)2.1.1.2)2.1.1)2.1)2)∧⊣$");
        testTree(504,"(a|a*)*","aa","(∧(1(1.2(1.2.1a1.2.1)1.2.1(1.2.1a1.2.1)1.2.1)1.2)1)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(505,"(a*|a)*","aa","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1)1)∧⊣$",null,"(∧(1aa)1)∧⊣$");
        testTree(506,"a*|(a|b)*","aaa","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1(1.1a1.1)1.1)1)∧⊣$",null,"(∧(1aaa)1)∧⊣$");
        testTree(5061,"((a)*)|(((a)|(b))*)","aaa","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1)1)∧⊣$");
        testTree(507,"(a|ab)(c|bcd)(de|e)","abcde","(∧(1(1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1(1.1.2.2b1.1.2.2)1.1.2.2)1.1.2)1.1)1(2(2.1(2.1.1c2.1.1)2.1.1)2.1)2(3(3.1(3.1.1(3.1.1.1d3.1.1.1)3.1.1.1(3.1.1.2e3.1.1.2)3.1.1.2)3.1.1)3.1)3)∧⊣$",
            "(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(2(2.1(2.1.2(2.1.2.1b2.1.2.1)2.1.2.1(2.1.2.2c2.1.2.2)2.1.2.2(2.1.2.3d2.1.2.3)2.1.2.3)2.1.2)2.1)2(3(3.1(3.1.2e3.1.2)3.1.2)3.1)3)∧⊣$");
        testTree(508,"(a+|ba|aba)*b","abab","(∧(1(1.1(1.1.3(1.1.3.1a1.1.3.1)1.1.3.1(1.1.3.2b1.1.3.2)1.1.3.2(1.1.3.3a1.1.3.3)1.1.3.3)1.1.3)1.1)1(2b2)2)∧⊣$",
            "(∧(1(1.1(1.1.1(1.1.1.1a1.1.1.1)1.1.1.1)1.1.1)1.1(1.1(1.1.2(1.1.2.1b1.1.2.1)1.1.2.1(1.1.2.2a1.1.2.2)1.1.2.2)1.1.2)1.1)1(2b2)2)∧⊣$");
        testTree(509,"(a|b|ab)*","abab","(∧(1(1.3(1.3.1a1.3.1)1.3.1(1.3.2b1.3.2)1.3.2)1.3)1(1(1.3(1.3.1a1.3.1)1.3.1(1.3.2b1.3.2)1.3.2)1.3)1)∧⊣$",
            "(∧(1(1.1a1.1)1.1)1(1(1.2b1.2)1.2)1(1(1.1a1.1)1.1)1(1(1.2b1.2)1.2)1)∧⊣$");
        testTree(510,"a*aa","aaaa","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1(2a2)2(3a3)3)∧⊣$",null,"aaaa⊣$");
        testTree(511,"(((ab))|a()b)*","ab","(∧(1(1.1(1.1.1(1.1.1.1(1.1.1.1.1a1.1.1.1.1)1.1.1.1.1(1.1.1.1.2b1.1.1.1.2)1.1.1.1.2)1.1.1.1)1.1.1)1.1)1)∧⊣$",
            null,"(∧(1(1.1(1.1.1(1.1.1.1ab)1.1.1.1)1.1.1)1.1)1)∧⊣$");
        testTree(512,"(a*|a*a*)*b","b","(∧(1(1.1(1.1.1)1.1.1)1.1)1(2b2)2)∧⊣$",null,"(∧(1(1.1)1.1)1(2b2)2)∧⊣$");
        testTree(513,"(a*a*|a*)*b","b","(∧(1(1.1(1.1.1(1.1.1.1)1.1.1.1(1.1.1.2)1.1.1.2)1.1.1)1.1)1(2b2)2)∧⊣$",
            null,"(∧(1(1.1)1.1)1(2b2)2)∧⊣$");
        testTree(514,"(a)*(f|j|ajf)*","aajf","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1(2(2.1(2.1.2j2.1.2)2.1.2)2.1(2.1(2.1.1f2.1.1)2.1.1)2.1)2)∧⊣$",
            null,"(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1(2(2.1j)2.1(2.1f)2.1)2)∧⊣$");
        testTree(515,"(a|a)(b|b)","ab","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(2(2.1(2.1.1b2.1.1)2.1.1)2.1)2)∧⊣$",
            null,"(∧(1(1.1a)1.1)1(2(2.1b)2.1)2)∧⊣$");
        testTree(516,"a((b)?)*c","abbc","(∧(1a1)1(2(2.1(2.1.1b2.1.1)2.1.1)2.1(2.1(2.1.1b2.1.1)2.1.1)2.1)2(3c3)3)∧⊣$");
        testTree(517,"a|(a|b)","a","(∧(1a1)1)∧⊣$");
        testTree(518,"a|(a|b)","b","(∧(2(2.1(2.1.2b2.1.2)2.1.2)2.1)2)∧⊣$",null,"(∧(2(2.1b)2.1)2)∧⊣$");
        testTree(519,"(())*","","(∧(1(1.1)1.1)1)∧⊣$");
        testTree(520,"(a)*(a)*a","aa","(∧(1(1.1a1.1)1.1)1(2)2(3a3)3)∧⊣$");

        testTree(600,"","","(∧)∧⊣$",null,"⊣$");
        testTree(601,"a","a","(∧a∧)∧⊣$",null,"a⊣$");
        testTree(602,"abc","abc","(∧(1a1)1(2b2)2(3c3)3)∧⊣$",null,"abc⊣$");
        testTree(603,"a|bc","a","(∧(1a1)1)∧⊣$",null,"a⊣$");
        testTree(604,"a|bc","bc","(∧(2(2.1b2.1)2.1(2.2c2.2)2.2)2)∧⊣$",null,"bc⊣$");
        testTree(605,"a(b)c","abc","(∧(1a1)1(2(2.1b2.1)2.1)2(3c3)3)∧⊣$");
        testTree(606,"a(bc)d","abcd","(∧(1a1)1(2(2.1(2.1.1b2.1.1)2.1.1(2.1.2c2.1.2)2.1.2)2.1)2(3d3)3)∧⊣$",null,"(∧(1a1)1(2(2.1bc)2.1)2(3d3)3)∧⊣$");
        testTree(607,"a(b|cd)e","abe","(∧(1a1)1(2(2.1(2.1.1b2.1.1)2.1.1)2.1)2(3e3)3)∧⊣$",null,"(∧(1a1)1(2(2.1b)2.1)2(3e3)3)∧⊣$");
        testTree(608,"a(b|cd)e","acde","(∧(1a1)1(2(2.1(2.1.2(2.1.2.1c2.1.2.1)2.1.2.1(2.1.2.2d2.1.2.2)2.1.2.2)2.1.2)2.1)2(3e3)3)∧⊣$",
            null,"(∧(1a1)1(2(2.1cd)2.1)2(3e3)3)∧⊣$");
        testTree(609,"a*","a","(∧(1a1)1)∧⊣$",null,"a⊣$");
        testTree(610,"(a)","a","(∧(1a1)1)∧⊣$");
        testTree(611,"a*","aa","(∧(1a1)1(1a1)1)∧⊣$",null,"aa⊣$");
        testTree(612,"ab*c","abc","(∧(1a1)1(2(2.1b2.1)2.1)2(3c3)3)∧⊣$",null,"abc⊣$");
        testTree(611,"a*","","(∧)∧⊣$",null,"⊣$");
        testTree(613,"a+","a","(∧(1a1)1)∧⊣$",null,"a⊣$");
        testTree(614,"(a)?","","(∧)∧⊣$");
        testTree(615,"(a)?","a","(∧(1a1)1)∧⊣$");
        testTree(616,"a*b","b","(∧(1)1(2b2)2)∧⊣$",null,"b⊣$");
        testTree(617,"((xx)(a|b|ab)*)*","xxab","(∧(1(1.1(1.1.1(1.1.1.1x1.1.1.1)1.1.1.1(1.1.1.2x1.1.1.2)1.1.1.2)1.1.1)1.1(1.2(1.2.1(1.2.1.3(1.2.1.3.1a1.2.1.3.1)1.2.1.3.1(1.2.1.3.2b1.2.1.3.2)1.2.1.3.2)1.2.1.3)1.2.1)1.2)1)∧⊣$",
            "(∧(1(1.1(1.1.1(1.1.1.1x1.1.1.1)1.1.1.1(1.1.1.2x1.1.1.2)1.1.1.2)1.1.1)1.1(1.2(1.2.1(1.2.1.1a1.2.1.1)1.2.1.1)1.2.1(1.2.1(1.2.1.2b1.2.1.2)1.2.1.2)1.2.1)1.2)1)∧⊣$");
        testTree(618,"a+","aa","(∧(1a1)1(1a1)1)∧⊣$",null,"aa⊣$");
        testTree(619,"a+b","aab","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1)1(2b2)2)∧⊣$",null,"aab⊣$");
        testTree(620,"a+b|cd*","aab","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1(1.2b1.2)1.2)1)∧⊣$",null,"aab⊣$");
        testTree(621,"a+b|cd*","cdd","(∧(2(2.1c2.1)2.1(2.2(2.2.1d2.2.1)2.2.1(2.2.1d2.2.1)2.2.1)2.2)2)∧⊣$",null,"cdd⊣$");
        testTree(622,"a+a*","aaa","(∧(1(1.1a1.1)1.1(1.1a1.1)1.1(1.1a1.1)1.1)1(2)2)∧⊣$",null,"aaa⊣$");
        testTree(623,"(a*b)*","aabab","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1(1.2b1.2)1.2)1(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.2b1.2)1.2)1)∧⊣$",null,"(∧(1aab)1(1ab)1)∧⊣$");
        testTree(624,"((a|){2,3}){2}","aa","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1)1)∧⊣$",
             "(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.2)1.1.2)1.1)1(1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1)1)∧⊣$","(∧(1(1.1a)1.1(1.1a)1.1)1(1(1.1)1.1(1.1)1.1)1)∧⊣$");

        testTree(700,"abc","ab","error");
        testTree(701,"ab","abc","error");
        testTree(702,"abd","acd","error");
        testTree(703,"ab(d)?","abc","error");

        // failures
        testTree(800,"a*bc","b","error");
        testTree(801,"a(b)c","ac","error");
        testTree(802,"abc*","a","error");
        testTree(803,"a|b|c","d","error");
        testTree(804,"abc","abcd","error");
        testTree(805,"a+bc","bc","error");
        testTree(806,"ab+c","ac","error");
        testTree(807,"abc+","ab","error");
        testTree(808,"a(b)?c","adc","error");
        testTree(809,"a(b)?c","abbc","error");
        testTree(810,"a(b)c","ac","error");
        testTree(811,"a(b|d)c","ac","error");
        testTree(812,"a(b|d)c","aac","error");
        testTree(813,"a(b|dd)c","adc","error");
        testTree(814,"a(b|d+)c","ac","error");
        testTree(815,"a(b|(d)?)c","addc","error");
        testTree(816,"a","","error");
        testTree(817,"a(b|d)","abc","error");
        // problematic
        testTree(900,"(a|)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$",null,"(∧(1a)1)∧⊣$");
        testTree(901,"(a|())*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(902,"(a|()*)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(903,"(a|(b)*)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(904,"(a|(a|b)*)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$");
        testTree(905,"(a|(a)*|(a|c)*)*","a","(∧(1(1.1a1.1)1.1)1)∧⊣$");
        this.altbin = true;
        testTree(906,"(a|(a)*|(a|c)*)*","a","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1)1)∧⊣$");
        this.altbin = false;
        testTree(907,"a***","aaa","(∧(1(1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1(1.1.1a1.1.1)1.1.1)1.1)1)∧⊣$",null,"aaa⊣$");
        testTree(908,"((a|){2,3}){2}","aa","(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.1a1.1.1)1.1.1)1.1)1(1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1)1)∧⊣$",
            "(∧(1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.1a1.1.1)1.1.1)1.1(1.1(1.1.2)1.1.2)1.1)1(1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1(1.1(1.1.2)1.1.2)1.1)1)∧⊣$");
        testTree(909,"(a|)*","","(∧(1(1.2)1.2)1)∧⊣$",null,"(∧(1)1)∧⊣$");

        // cyclic bijection
//settrc("tv");
//settrc("");
        testTree(950,"(([ab][b]?)([bc][ac])?)*","","(∧)∧⊣$");
        testTree(951,"(([bc][ab][a]?)([ab][bc])?)*","","(∧)∧⊣$");
        testTree(952,"([a]*|([ac][c])*)*([bc][b])*","","(∧(1(1.1(1.1.1)1.1.1)1.1)1(2)2)∧⊣$");
        testTree(953,"([ab]*[b])([ab][ab])+","bbb","(∧(1(1.1(1.1.1)1.1.1(1.1.2b1.1.2)1.1.2)1.1)1(2(2.1(2.1.1b2.1.1)2.1.1(2.1.2b2.1.2)2.1.2)2.1)2)∧⊣$",
            null,"(∧(1(1.1b)1.1)1(2(2.1bb)2.1)2)∧⊣$");
        testTree(954,"(aaaaa|aaa)*a*","aaaaaaa",
            "(∧(1(1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1(1.1.2.2a1.1.2.2)1.1.2.2(1.1.2.3a1.1.2.3)1.1.2.3)1.1.2)1.1" +
            "(1.1(1.1.2(1.1.2.1a1.1.2.1)1.1.2.1(1.1.2.2a1.1.2.2)1.1.2.2(1.1.2.3a1.1.2.3)1.1.2.3)1.1.2)1.1)1" +
            "(2(2.1a2.1)2.1)2)∧⊣$",
            "(∧(1(1.1(1.1.1(1.1.1.1a1.1.1.1)1.1.1.1(1.1.1.2a1.1.1.2)1.1.1.2(1.1.1.3a1.1.1.3)1.1.1.3" +
            "(1.1.1.4a1.1.1.4)1.1.1.4(1.1.1.5a1.1.1.5)1.1.1.5)1.1.1)1.1)1(2(2.1a2.1)2.1(2.1a2.1)2.1)2)∧⊣$");
        feature("Final registers");
        testFinreg(0,"a|b","a",testFinregAlgos);
        testFinreg(1,"a|(b)","a",testFinregAlgos);
        testFinreg(2,"a|(b)?","a",testFinregAlgos);
        testFinreg(3,"a|(b)?","",testFinregAlgos);
        testFinreg(4,"a|(b)*","b",testFinregAlgos);
        testFinreg(5,"a|(b)*","",testFinregAlgos);
        testFinreg(6,"a|(b){0,2}","bb",testFinregAlgos);
        testFinreg(7,"a|(b){0,2}","b",testFinregAlgos);
        testFinreg(8,"a|(b){0,2}","",testFinregAlgos);
        testFinreg(20,"a|b","a",testFinregPartAlgos);
        testFinreg(21,"(a|b)","a",testFinregPartAlgos);
        testFinreg(22,"a|(b)","a",testFinregPartAlgos);

        this.posix = false;
        this.autotags = false;
        this.incremental = false;
        this.posix = true;
        this.autotags = true;

        feature("Result");
        testResult(1,"negtags,posix,lookahead,transtable,useTnfa,matchTstring");
        testResult(2,"negtags,posix,lookahead,transtable,useTnfa,finreg");
        testResult(3,"negtags,posix,lookahead,transtable,useTnfa,matchTstring,finreg");
        testResult(4,"negtags,posix,lookahead,transtable,useTnfa,tagless,matchTstring");
        testResult(5,"negtags,posix,lookahead,transtable,useTnfa,tagless,finreg");
        testResult(6,"negtags,posix,lookahead,transtable,useTnfa,tagless,matchTstring,finreg");
        testResult(7,"negtags,posix,lookahead,transtable,useTnfa,matchTstring");
        testResult(8,"negtags,posix,lookahead,transtable,useTnfa,incremental,finreg");
        testResult(9,"negtags,posix,lookahead,transtable,useTnfa,incremental,matchTstring,finreg");
        testResult(10,"negtags,posix,lookahead,transtable,useTnfa,incremental,tagless,matchTstring");
        testResult(11,"negtags,posix,lookahead,transtable,useTnfa,incremental,tagless,finreg");
        testResult(12,"negtags,posix,lookahead,transtable,useTnfa,incremental,tagless,matchTstring,finreg");
        testResult(13,"negtags,posix,lookahead,transtable,matchTstring");
        testResult(14,"negtags,posix,lookahead,transtable,finreg");
        testResult(15,"negtags,posix,lookahead,transtable,matchTstring,finreg");
        testResult(16,"negtags,posix,lookahead,transtable,tagless,matchTstring");
        testResult(17,"negtags,posix,lookahead,transtable,tagless,finreg");
        testResult(18,"negtags,posix,lookahead,transtable,tagless,matchTstring,finreg");

        feature("Fowler");
        this.altbin = true;
        this.noGRO = false;
        this.tagless = false;
        this.autotags = true;
        this.finreg = false;
        this.okui = false;
        testFowler(1,"a+","xaax","(1,3)");
        testFowler(2,".(a*).","xaax","(0,4)(1,3)");
        testFowler(3,"(a?)((ab)?)","ab","(0,2)(0,0)(0,2)(0,2)");
        testFowler(4,"(a?)((ab)?)(b?)","ab","(0,2)(0,1)(1,1)(?,?)(1,2)");
        testFowler(5,"((a?)((ab)?))(b?)","ab","(0,2)(0,2)(0,0)(0,2)(0,2)(2,2)");
        testFowler(6,"(a?)(((ab)?)(b?))","ab","(0,2)(0,1)(1,2)(1,1)(?,?)(1,2)");
        testFowler(7,"(.?)","x","(0,1)(0,1)");
        testFowler(8,"(.?){1}","x","(0,1)(0,1)");
        testFowler(9,"(.?)(.?)","x","(0,1)(0,1)(1,1)");
        testFowler(10,"(.?){2}","x","(0,1)(1,1)");
        testFowler(11,"(.?)*","x","(0,1)(0,1)");
        testFowler(12,"(.?.?)","xxx","(0,2)(0,2)");
        testFowler(13,"(.?.?){1}","xxx","(0,2)(0,2)");
        testFowler(14,"(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)");
        testFowler(15,"(.?.?){2}","xxx","(0,3)(2,3)");
        testFowler(16,"(.?.?)(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)(3,3)");
        testFowler(17,"(.?.?){3}","xxx","(0,3)(3,3)");
        testFowler(18,"(.?.?)*","xxx","(0,3)(2,3)");
        testFowler(19,"a?((ab)?)(b?)","ab","(0,2)(1,1)(?,?)(1,2)");
        testFowler(20,"(a?)((ab)?)b?","ab","(0,2)(0,1)(1,1)(?,?)");
        testFowler(21,"a?((ab)?)b?","ab","(0,2)(1,1)(?,?)");
        testFowler(22,"(a*){2}","xxxxx","(0,0)(0,0)");
        testFowler(23,"(ab?)(b?a)","aba","(0,3)(0,2)(2,3)");
        testFowler(24,"(a|ab)(ba|a)","aba","(0,3)(0,2)(2,3)");
        testFowler(25,"(a|ab|ba)","aba","(0,2)(0,2)");
        testFowler(26,"(a|ab|ba)(a|ab|ba)","aba","(0,3)(0,2)(2,3)");
        testFowler(27,"(a|ab|ba)*","aba","(0,3)(2,3)");
        testFowler(28,"(aba|a*b)","ababa","(0,3)(0,3)");
        testFowler(29,"(aba|a*b)(aba|a*b)","ababa","(0,5)(0,2)(2,5)");
        testFowler(30,"(aba|a*b)*","ababa","(0,5)(2,5)");
        testFowler(31,"(aba|ab|a)","ababa","(0,3)(0,3)");
        testFowler(32,"(aba|ab|a)(aba|ab|a)","ababa","(0,5)(0,2)(2,5)");
        testFowler(33,"(aba|ab|a)*","ababa","(0,5)(2,5)");
        testFowler(34,"(a(b)?)","aba","(0,2)(0,2)(1,2)");
        testFowler(35,"(a(b)?)(a(b)?)","aba","(0,3)(0,2)(1,2)(2,3)(?,?)");
        testFowler(36,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testFowler(37,"(.*)(.*)","xx","(0,2)(0,2)(2,2)");
        testFowler(38,".*(.*)","xx","(0,2)(2,2)");
        testFowler(39,"(a.*z|b.*y)","azbazby","(0,5)(0,5)");
        testFowler(40,"(a.*z|b.*y)(a.*z|b.*y)","azbazby","(0,7)(0,5)(5,7)");
        testFowler(41,"(a.*z|b.*y)*","azbazby","(0,7)(5,7)");
        testFowler(42,"(.|..)(.*)","ab","(0,2)(0,2)(2,2)");
        testFowler(43,"((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)");
        testFowler(44,"((..)*(...)*)((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)(3,3)(?,?)(?,?)");
        testFowler(45,"((..)*(...)*)*","xxx","(0,3)(0,3)(?,?)(0,3)");
        testFowler(83,"(aa(b(b))?)+","aabbaa","(0,6)(4,6)(?,?)(?,?)");
        testFowler(84,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testFowler(85,"([ab]+)([bc]+)([cd]*)","abcd","(0,4)(0,2)(2,3)(3,4)");
        testFowler(86,"a(b)?","a","(0,1)(?,?)");
        testFowler(87,"a(b){0,1}","a","(0,1)(?,?)");
        testFowler(88,"ab?","a","(0,1)");
        testFowler(89,"(ab|(a)*)*","aba","(0,3)(2,3)(2,3)");

        this.re2c_nfa = false;
        feature("RE2C");
        testRE2C(1,"a","a","(0,1)");
        testRE2C(2,".(a*).","xaax","(0,4)(1,3)");
        testRE2C(3,"(a?)((ab)?)","ab","(0,2)(0,0)(0,2)(0,2)");
        testRE2C(4,"(a?)((ab)?)(b?)","ab","(0,2)(0,1)(1,1)(?,?)(1,2)");
        testRE2C(5,"((a?)((ab)?))(b?)","ab","(0,2)(0,2)(0,0)(0,2)(0,2)(2,2)");
        testRE2C(6,"(a?)(((ab)?)(b?))","ab","(0,2)(0,1)(1,2)(1,1)(?,?)(1,2)");
        testRE2C(7,"(.?)","x","(0,1)(0,1)");
        testRE2C(8,"(.?){1}","x","(0,1)(0,1)");
        testRE2C(9,"(.?)(.?)","x","(0,1)(0,1)(1,1)");
        testRE2C(10,"(.?){2}","x","(0,1)(1,1)");
        testRE2C(11,"(.?)*","x","(0,1)(0,1)");
        testRE2C(12,"(.?.?)","xxx","(0,2)(0,2)");
        testRE2C(13,"(.?.?){1}","xxx","(0,2)(0,2)");
        testRE2C(14,"(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)");
        testRE2C(15,"(.?.?){2}","xxx","(0,3)(2,3)");
        testRE2C(16,"(.?.?)(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)(3,3)");
        testRE2C(17,"(.?.?){3}","xxx","(0,3)(3,3)");
        testRE2C(18,"(.?.?)*","xxx","(0,3)(2,3)");
        testRE2C(19,"a?((ab)?)(b?)","ab","(0,2)(1,1)(?,?)(1,2)");
        testRE2C(20,"(a?)((ab)?)b?","ab","(0,2)(0,1)(1,1)(?,?)");
        testRE2C(21,"a?((ab)?)b?","ab","(0,2)(1,1)(?,?)");
        testRE2C(22,"(a*){2}","xxxxx","(0,0)(0,0)");
        testRE2C(23,"(ab?)(b?a)","aba","(0,3)(0,2)(2,3)");
        testRE2C(24,"(a|ab)(ba|a)","aba","(0,3)(0,2)(2,3)");
        testRE2C(25,"(a|ab|ba)","aba","(0,2)(0,2)");
        testRE2C(26,"(a|ab|ba)(a|ab|ba)","aba","(0,3)(0,2)(2,3)");
        testRE2C(27,"(a|ab|ba)*","aba","(0,3)(2,3)");
        testRE2C(28,"(aba|a*b)","ababa","(0,3)(0,3)");
        testRE2C(29,"(aba|a*b)(aba|a*b)","ababa","(0,5)(0,2)(2,5)");
        testRE2C(30,"(aba|a*b)*","ababa","(0,5)(2,5)");
        testRE2C(31,"(aba|ab|a)","ababa","(0,3)(0,3)");
        testRE2C(32,"(aba|ab|a)(aba|ab|a)","ababa","(0,5)(0,2)(2,5)");
        testRE2C(33,"(aba|ab|a)*","ababa","(0,5)(2,5)");
        testRE2C(34,"(a(b)?)","aba","(0,2)(0,2)(1,2)");
        testRE2C(35,"(a(b)?)(a(b)?)","aba","(0,3)(0,2)(1,2)(2,3)(?,?)");
        testRE2C(36,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testRE2C(37,"(.*)(.*)","xx","(0,2)(0,2)(2,2)");
        testRE2C(38,".*(.*)","xx","(0,2)(2,2)");
        testRE2C(39,"(a.*z|b.*y)","azbazby","(0,5)(0,5)");
        testRE2C(40,"(a.*z|b.*y)(a.*z|b.*y)","azbazby","(0,7)(0,5)(5,7)");
        testRE2C(41,"(a.*z|b.*y)*","azbazby","(0,7)(5,7)");
        testRE2C(42,"(.|..)(.*)","ab","(0,2)(0,2)(2,2)");
        testRE2C(43,"((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)");
        testRE2C(44,"((..)*(...)*)((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)(3,3)(?,?)(?,?)");
        testRE2C(45,"((..)*(...)*)*","xxx","(0,3)(0,3)(?,?)(0,3)");
        testRE2C(83,"(aa(b(b))?)+","aabbaa","(0,6)(4,6)(?,?)(?,?)");
        testRE2C(84,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testRE2C(85,"([ab]+)([bc]+)([cd]*)","abcd","(0,4)(0,2)(2,3)(3,4)");
        testRE2C(86,"a(b)?","a","(0,1)(?,?)");
        testRE2C(87,"a(b){0,1}","a","(0,1)(?,?)");
        testRE2C(88,"ab?","a","(0,1)");

        this.re2c_nfa = true;
        feature("RE2C");
        testRE2C(1,"a","a","(0,1)");
        testRE2C(2,".(a*).","xaax","(0,4)(1,3)");
        testRE2C(3,"(a?)((ab)?)","ab","(0,2)(0,0)(0,2)(0,2)");
        testRE2C(4,"(a?)((ab)?)(b?)","ab","(0,2)(0,1)(1,1)(?,?)(1,2)");
        testRE2C(5,"((a?)((ab)?))(b?)","ab","(0,2)(0,2)(0,0)(0,2)(0,2)(2,2)");
        testRE2C(6,"(a?)(((ab)?)(b?))","ab","(0,2)(0,1)(1,2)(1,1)(?,?)(1,2)");
        testRE2C(7,"(.?)","x","(0,1)(0,1)");
        testRE2C(8,"(.?){1}","x","(0,1)(0,1)");
        testRE2C(9,"(.?)(.?)","x","(0,1)(0,1)(1,1)");
        testRE2C(10,"(.?){2}","x","(0,1)(1,1)");
        testRE2C(11,"(.?)*","x","(0,1)(0,1)");
        testRE2C(12,"(.?.?)","xxx","(0,2)(0,2)");
        testRE2C(13,"(.?.?){1}","xxx","(0,2)(0,2)");
        testRE2C(14,"(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)");
        testRE2C(15,"(.?.?){2}","xxx","(0,3)(2,3)");
        testRE2C(16,"(.?.?)(.?.?)(.?.?)","xxx","(0,3)(0,2)(2,3)(3,3)");
        testRE2C(17,"(.?.?){3}","xxx","(0,3)(3,3)");
        testRE2C(18,"(.?.?)*","xxx","(0,3)(2,3)");
        testRE2C(19,"a?((ab)?)(b?)","ab","(0,2)(1,1)(?,?)(1,2)");
        testRE2C(20,"(a?)((ab)?)b?","ab","(0,2)(0,1)(1,1)(?,?)");
        testRE2C(21,"a?((ab)?)b?","ab","(0,2)(1,1)(?,?)");
        testRE2C(22,"(a*){2}","xxxxx","(0,0)(0,0)");
        testRE2C(23,"(ab?)(b?a)","aba","(0,3)(0,2)(2,3)");
        testRE2C(24,"(a|ab)(ba|a)","aba","(0,3)(0,2)(2,3)");
        testRE2C(25,"(a|ab|ba)","aba","(0,2)(0,2)");
        testRE2C(26,"(a|ab|ba)(a|ab|ba)","aba","(0,3)(0,2)(2,3)");
        testRE2C(27,"(a|ab|ba)*","aba","(0,3)(2,3)");
        testRE2C(28,"(aba|a*b)","ababa","(0,3)(0,3)");
        testRE2C(29,"(aba|a*b)(aba|a*b)","ababa","(0,5)(0,2)(2,5)");
        testRE2C(30,"(aba|a*b)*","ababa","(0,5)(2,5)");
        testRE2C(31,"(aba|ab|a)","ababa","(0,3)(0,3)");
        testRE2C(32,"(aba|ab|a)(aba|ab|a)","ababa","(0,5)(0,2)(2,5)");
        testRE2C(33,"(aba|ab|a)*","ababa","(0,5)(2,5)");
        testRE2C(34,"(a(b)?)","aba","(0,2)(0,2)(1,2)");
        testRE2C(35,"(a(b)?)(a(b)?)","aba","(0,3)(0,2)(1,2)(2,3)(?,?)");
        testRE2C(36,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testRE2C(37,"(.*)(.*)","xx","(0,2)(0,2)(2,2)");
        testRE2C(38,".*(.*)","xx","(0,2)(2,2)");
        testRE2C(39,"(a.*z|b.*y)","azbazby","(0,5)(0,5)");
        testRE2C(40,"(a.*z|b.*y)(a.*z|b.*y)","azbazby","(0,7)(0,5)(5,7)");
        testRE2C(41,"(a.*z|b.*y)*","azbazby","(0,7)(5,7)");
        testRE2C(42,"(.|..)(.*)","ab","(0,2)(0,2)(2,2)");
        testRE2C(43,"((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)");
        testRE2C(44,"((..)*(...)*)((..)*(...)*)","xxx","(0,3)(0,3)(?,?)(0,3)(3,3)(?,?)(?,?)");
        testRE2C(45,"((..)*(...)*)*","xxx","(0,3)(0,3)(?,?)(0,3)");
        testRE2C(83,"(aa(b(b))?)+","aabbaa","(0,6)(4,6)(?,?)(?,?)");
        testRE2C(84,"(a(b)?)+","aba","(0,3)(2,3)(?,?)");
        testRE2C(85,"([ab]+)([bc]+)([cd]*)","abcd","(0,4)(0,2)(2,3)(3,4)");
        testRE2C(86,"a(b)?","a","(0,1)(?,?)");
        testRE2C(87,"a(b){0,1}","a","(0,1)(?,?)");
        testRE2C(88,"ab?","a","(0,1)");

        this.autotags = true;
        this.astGroups = AST_GROUPS_ONE;

        feature("BoolSet");
        testBoolSetAssign(0,"[a-f]");
        testBoolSetAssign(1,"[a-fp-s]");
        testBoolSetAssign(2,"[a]");
        testBoolSetRange(3,'a','f',"[a-e]");
        testBoolSetSet(4,'a',true,"[a]");
        testBoolSetComp(5,"[a-f]");
        testBoolSetOper(6,"[a-f]","or","[a-f]","[a-f]");
        testBoolSetOper(7,"[b-f]","or","[a-h]","[a-h]");
        testBoolSetOper(8,"[a-f]","or","[b-g]","[a-g]");
        testBoolSetOper(9,"[a-f]","or","[p-r]","[a-fp-r]");
        testBoolSetOper(10,"[a-f]","and","[a-f]","[a-f]");
        testBoolSetOper(11,"[b-f]","and","[a-h]","[b-f]");
        testBoolSetOper(12,"[a-f]","and","[b-g]","[b-f]");
        testBoolSetOper(13,"[a-f]","and","[p-r]","[]");
        testBoolSetOper(14,"[a-f]","sub","[a-b]","[c-f]");
        testBoolSetOper(15,"[a-f]","sub","[b-d]","[aef]");
        testBoolSetOper(16,"[a-f]","sub","[f-h]","[a-e]");
        testBoolSetOper(17,"[a-f]","sub","[g-l]","[a-f]");
        testBoolSetEmpty(18,"[]",true);
        testBoolSetEmpty(19,"[a]",false);
        testBoolSetEquals(20,"[a-f]","[a-f]",true);
        testBoolSetEquals(21,"[a-f]","[b-f]",false);
        testBoolSetCompare(22,"[a-f]","[a-f]",0);
        testBoolSetCompare(23,"[ac-f]","[ad-f]",-1);
        testBoolSetCompare(24,"[ad-f]","[ac-f]",1);
        testBoolSetCompare(25,"[]","[a-f]",-1);

        feature("Symbol classes");
        testSymClass(0,"0:[b-e]->1; 1:[c-f]->2","0-ag-127,b,c-e,f");
        testSymClass(1,"0:[b-e]->1; 1:[g-h]->2","0-afi-127,b-e,gh");
        testSymClass(2,"0:[b-p]->1; 1:[g-h]->2","0-aq-127,b-fi-p,gh");


        System.out.printf("totconfig %s\n",totconfig);
        if (testErrors > 0){
            System.out.printf("end test cases %s tests failed\n",testErrors);
            System.exit(1);
        }

        ReTdfa[] rearr = null;
        // automaton (N: TNFA, D: TDFA)
        // tag density (F: full tags, P: partial tags, M: one tag)
        // parse results (O: last offsets, H: subhistories, T: t-string)
        // registers (R: register, L: regless)

        ReTdfa[] rearrN = new ReTdfa[]{
            new ReTdfa("NFHR","negtags,posix,transtable,lookahead,okui,incremental,useTnfa,autotags,finreg"),
            new ReTdfa("NFTL","negtags,posix,transtable,lookahead,okui,incremental,useTnfa,autotags,matchTstring,tagless"),
            new ReTdfa("NPHR","negtags,posix,transtable,lookahead,okui,incremental,useTnfa,finreg"),
            new ReTdfa("NPTL","negtags,posix,transtable,lookahead,okui,incremental,useTnfa,matchTstring,tagless"),
            new ReTdfa("NMHR","negtags,transtable,lookahead,incremental,useTnfa,onetag,finreg"),
            new ReTdfa("NMTL","negtags,transtable,lookahead,incremental,useTnfa,onetag,matchTstring,tagless"),
        };

        ReTdfa[] rearrDPO = new ReTdfa[]{
            new ReTdfa("DPOR",      "negtags,posix,transtable,lookahead,okui,altbin,offsets,lastval"),
            new ReTdfa("DPOL",      "negtags,posix,transtable,lookahead,okui,altbin,offsets,lastval,tagless"),
            new ReTdfa("DPOR-re2c", "re2c"),
            new ReTdfa("DPOL-re2c", "re2c,re2c_regless"),
        };

        ReTdfa[] rearrDPH = new ReTdfa[]{
            new ReTdfa("DPHR",      "negtags,posix,transtable,lookahead,okui,altbin,finreg"),
            new ReTdfa("DPHL",      "negtags,posix,transtable,lookahead,okui,altbin,finreg,tagless"),
            new ReTdfa("DPHR-re2c", "re2c,re2c_subhist"),
            new ReTdfa("DPHL-re2c", "re2c,re2c_subhist,re2c_regless"),
        };

        ReTdfa[] rearrDPT = new ReTdfa[]{
            new ReTdfa("DPTL",      "negtags,posix,transtable,lookahead,okui,altbin,matchTstring,tagless"),
            new ReTdfa("DPTL-re2c", "re2c,re2c_tstring,re2c_regless"),
        };

        ReTdfa[] rearrDFO = new ReTdfa[]{
            new ReTdfa("DFOR",      "negtags,posix,transtable,lookahead,okui,altbin,autotags,offsets,lastval"),
            new ReTdfa("DFOL",      "negtags,posix,transtable,lookahead,okui,altbin,autotags,offsets,lastval,tagless"),
            new ReTdfa("DFOR-re2c", "re2c,re2c_autotags"),
            new ReTdfa("DFOL-re2c", "re2c,re2c_autotags,re2c_regless"),
        };

        ReTdfa[] rearrDFH = new ReTdfa[]{
            new ReTdfa("DFHR",      "negtags,posix,transtable,lookahead,okui,altbin,autotags,finreg"),
            new ReTdfa("DFHL",      "negtags,posix,transtable,lookahead,okui,altbin,autotags,finreg,tagless"),
            new ReTdfa("DFHR-re2c", "re2c,re2c_autotags,re2c_subhist"),
            new ReTdfa("DFHL-re2c", "re2c,re2c_autotags,re2c_subhist,re2c_regless"),
        };

        ReTdfa[] rearrDFT = new ReTdfa[]{
            new ReTdfa("DFTL",      "negtags,posix,transtable,lookahead,okui,autotags,altbin,matchTstring,tagless"),
            new ReTdfa("DFTL-re2c", "re2c,re2c_autotags,re2c_tstring,re2c_regless"),
        };

        ReTdfa[] rearrDP = concatArrays(rearrDPO, concatArrays(rearrDPH, rearrDPT));
        ReTdfa[] rearrDF = concatArrays(rearrDFO, concatArrays(rearrDFH, rearrDFT));

        //bench(rearrN,   "measure_N.ser",   "chart_N.html");
        bench(rearrDPO, "measure_DPO.ser", "chart_DPO.html");
        bench(rearrDPH, "measure_DPH.ser", "chart_DPH.html");
        bench(rearrDPT, "measure_DPT.ser", "chart_DPT.html");
        bench(rearrDFO, "measure_DFO.ser", "chart_DFO.html");
        bench(rearrDFH, "measure_DFH.ser", "chart_DFH.html");
        bench(rearrDFT, "measure_DFT.ser", "chart_DFT.html");
        bench(rearrDP,  "measure_DP.ser",  "chart_DP.html");
        bench(rearrDF,  "measure_DF.ser",  "chart_DF.html");

        if (testErrors > 0){
            System.out.printf("end test %s tests failed\n",testErrors);
        } else {
            System.out.printf("all test passed\n");
        }

        // ---------------- DEBUG ----------------

        String str = "edaaieeazedaaieeazedaaieeaz";
        ReTdfa re = new ReTdfa();
        // altbin,concbin added in options to match libre2c construction
        re.setOptions("","negtags,posix,lookahead,transtable,okui,autotags,altbin,concbin,matchTstring,tagless");
        if (!re.compile("((edaaieea)z)*")){
            System.out.printf("compile error\n");
        }
        if (!re.match(str)){
            System.out.printf("match error\n");
        }
        System.out.printf("   %s\n", new Tstring(re.treearr).toString());

        // {1} added in RE to match ReTdfa construction
        long reg = RE2C.regcomp("((edaaieea){1}z)*", false, true, false, true, true);
        if (reg == 0) {
            System.out.printf("regcomp failed on RE %s\n", re);
        }
        if (RE2C.regexec(reg, str) != 0) {
            System.out.printf("regexec failed on RE %s, string %s\n", re, str);
        }
        System.out.printf("   %s\n", RE2C.showTstring(RE2C.getTstring(reg)));
    }

    public <T> T[] concatArrays(T[] a, T[] b) {
        int aLen = a.length;
        int bLen = b.length;

        @SuppressWarnings("unchecked")
        T[] c = (T[]) Array.newInstance(a.getClass().getComponentType(), aLen + bLen);
        System.arraycopy(a, 0, c, 0, aLen);
        System.arraycopy(b, 0, c, aLen, bLen);

        return c;
    }

    private static String rep(String s, int n){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++){
            sb.append(s);
        }
        return sb.toString();
    }


    private void toSulz(int t, String re, String text){
        if (re.indexOf('{') >= 0 || re.indexOf('[') >= 0 || re.indexOf('.') >= 0){
            return;
        }
        ReTdfa r = new ReTdfa();
        r.setOptions("base","noGRO,negtags,autotags,posix,lookahead,transtable,tagless,parsetree,okui");
        if (!r.compile(re)){
            Trc.out.printf("!! %s compile error\n",re);
            return;
        }
        r.buildAst(re);
        astToBinary(r.astRoot);
        astSulz(r.astRoot);
        re = r.astRoot.toRE();

        r = new ReTdfa();
        r.setOptions("base","noGRO,negtags,autotags,posix,lookahead,transtable,tagless,parsetree,okui");
        // r.trc = this.trc;
        if (!r.compile(re)){
            Trc.out.printf("!! %s compile again error\n",re);
            return;
        }
        r.buildAst(re);
        r.match(text);
        re = r.astRoot.toRE().replaceAll("\\|","+");
        String sulztree = null;
        if (r.error){
            sulztree = "error";
        } else {
            sulztree = r.treeToSulz();
        }
        Trc.out.printf("    testParse(%s,\"%s\",\"%s\",\"%s\");\n",t,re,text,sulztree);
    }
    private void astToBinary(AstNode ast){
        switch (ast.kind){
        case A_LEA:      // leaf
            break;
        case A_ALT:      // alt
            if (ast.son.bro.bro == null){                          // two alternatives
                astToBinary(ast.son);
                astToBinary(ast.son.bro);
                break;
            }
            astToBinary(ast.son);
            AstNode bro = null;
            AstNode last = null;
            for (AstNode i = ast.son.bro; i.bro != null; i = bro){     // visit the 2..n ones
                last = i.bro;
                astToBinary(i);
                AstNode a = newAstNode(i.kind);
                a.groupKind = i.groupKind;
                a.son = i.son;
                a.bro = i.bro;
                a.sym = i.sym;
                a.altnr = 1;
                i.son = a;
                bro = i.bro;
                i.bro = null;
                i.kind = A_ALT;
                i.altnr = 2;
            }
            astToBinary(last);
            break;
        case A_CON:      // conc
            if (ast.son.bro.bro == null){                          // two sons
                astToBinary(ast.son);
                astToBinary(ast.son.bro);
                break;
            }
            astToBinary(ast.son);
            bro = null;
            last = null;
            for (AstNode i = ast.son.bro; i.bro != null; i = bro){     // visit the 2..n ones
                last = i.bro;
                astToBinary(i);
                AstNode a = newAstNode(i.kind);
                a.groupKind = i.groupKind;
                a.son = i.son;
                a.bro = i.bro;
                a.sym = i.sym;
                a.altnr = 0;
                i.son = a;
                bro = i.bro;
                i.bro = null;
                i.kind = A_CON;
                i.altnr = 0;
            }
            astToBinary(last);
            break;
        case A_GRO:      // group
            astToBinary(ast.son);
            break;
        case A_EMP:      // empty
        case A_NUL:      // phi
            break;
        }
    }
    private void astSulz(AstNode ast){
        switch (ast.kind){
        case A_GRO:      // group
            switch (ast.groupKind){
            case G_GRO:      // group
            case G_RE0:      // *
                break;
            case G_OPT:      // ?
                ast.groupKind = 0;             // epsilon | body
                ast.kind = A_ALT;
                AstNode son = ast.son;
                ast.son = newAstNode(A_EMP);
                ast.son.altnr = 1;
                ast.son.bro = son;
                ast.son.bro.altnr = 2;
                break;
            case G_RE1:      // +
                AstNode star = astDeepClone(ast);
                star.groupKind = G_RE0;
                son = ast.son;                 // body body*
                ast.groupKind = 0;
                ast.kind = A_CON;
                ast.son = son;
                ast.son.bro = star;
            }
        }
        for (AstNode i = ast.son; i != null; i = i.bro){
            astSulz(i);
        }
    }
    private AstNode astDeepClone(AstNode ast){
        AstNode node = newAstNode(ast.kind);
        node.groupKind = ast.groupKind;
        node.sym = ast.sym;
        node.altnr = ast.altnr;
        AstNode prev = null;
        for (AstNode i = ast.son; i != null; i = i.bro){
            if (i == ast.son){        // first
                node.son = astDeepClone(i);
                prev = node.son;
            } else {
                prev.bro = astDeepClone(i);
                prev = prev.bro;
            }
        }
        return node;
    }

    private String treeToSulz(){
        StringBuilder sb = new StringBuilder();
        DOM root = domRoot();
        treeToSulz(sb,root);
        return sb.toString();
    }
    private void treeToSulz(StringBuilder sb, DOM root){
        boolean open = false;
        boolean bropen = false;
        switch (root.nodeType){
        case DOM.T_LEAF:
            sb.append(this.text.substring(root.start,root.end));
            break;
        case DOM.T_ALT:
            DOM son = dom(root.firstChild);
            if (son.altNumber == 1){
                sb.append("Left");
            } else {
                sb.append("Right");
            }
            int kind = son.nodeType;
            if (kind >= DOM.T_GROUP) kind = dom(son.firstChild).nodeType;
            if (kind == DOM.T_ALT){
                sb.append("(");
                open = true;
            } else {
                sb.append(" ");
            }
            break;
        case DOM.T_CONC:
            sb.append("(");
            break;
        case DOM.T_EMPTY:
            sb.append("()");
            break;
        case DOM.T_STAR:
            sb.append("[");
            bropen = true;
            break;
        }
        if (root.childNodes != null){
            for (int i = 0; i < root.childNodes.length; i++){
                if (i > 0) sb.append(",");
                treeToSulz(sb,dom(root.childNodes[i]));
            }
        }
        switch (root.nodeType){
        case DOM.T_ALT:
            if (open) sb.append(")");
            break;
        case DOM.T_CONC:
            sb.append(")");
            break;
        case DOM.T_STAR:
            if (bropen) sb.append("]");
            break;
        }
    }



    /**
     * Measure the number of cycles taken by a System.nanotime().
     */

    private static long nanoBase(){
        long c0 = System.nanoTime();
        long c1 = System.nanoTime();
        long c2 = System.nanoTime();
        long c3 = System.nanoTime();
        long c4 = System.nanoTime();
        long c5 = System.nanoTime();
        long c6 = System.nanoTime();
        long c7 = System.nanoTime();
        long c8 = System.nanoTime();
        long c9 = System.nanoTime();
        long min = c1-c0;
        min = Math.min(min,c2-c1);
        min = Math.min(min,c3-c2);
        min = Math.min(min,c4-c3);
        min = Math.min(min,c5-c4);
        min = Math.min(min,c6-c5);
        min = Math.min(min,c7-c6);
        min = Math.min(min,c8-c7);
        min = Math.min(min,c9-c8);
        // System.out.printf("%s\n",min);
        return min;
    }

    /** The number of nanoseconds between two immediateli consecutive System.nanoTime() calls. */
    private static long NANO_BASE;

    /**
     * Record the number of nanoseconds taken by a System.nanotime().
     */

    static void getNanoBase(){
        long min = Long.MAX_VALUE;
        for (int i = 0; i < 10000; i++){
            NANO_BASE = Math.min(min,nanoBase());
        }
        System.out.printf("minimum nanoseconds measured %s\n",NANO_BASE);
    }

    /**
     * Main program.
     *
     * @param      args vector of the arguments
     */

    public static void main(String[] args){
        Locale.setDefault(Locale.US);
        getNanoBase();
        ReTdfa regex = new ReTdfa();
        regex.test();
    }
}
