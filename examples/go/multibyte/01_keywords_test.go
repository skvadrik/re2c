package main

import (
	"testing"
	"unsafe"
)

var testKeywords = []struct {
	input string
	want  int
}{
	{"SELECT\x00", TokSelect},
	{"INSERT\x00", TokInsert},
	{"UPDATE\x00", TokUpdate},
	{"DELETE\x00", TokDelete},
	{"FROM\x00", TokFrom},
	{"WHERE\x00", TokWhere},
	{"SELEC\x00", TokUnknown},
	{"SELECTT\x00", TokUnknown},
	{"\x00", TokUnknown},
	{"XYZ\x00", TokUnknown},
	{"DEL\x00", TokUnknown},
	{"UPDAT\x00", TokUnknown},
}

func TestKeywords_Parity(t *testing.T) {
	for _, tt := range testKeywords {
		gotVec := LexKeyword(tt.input)
		gotScalar := LexKeywordScalar(tt.input)

		if gotVec != tt.want {
			t.Errorf("LexKeyword(%q) = %d, attendu %d", tt.input, gotVec, tt.want)
		}
		if gotScalar != tt.want {
			t.Errorf("LexKeywordScalar(%q) = %d, attendu %d", tt.input, gotScalar, tt.want)
		}
		if gotVec != gotScalar {
			t.Errorf("Divergence sur %q: vectorisé=%d, scalaire=%d", tt.input, gotVec, gotScalar)
		}
	}
}

// Corpus réel de tokens SQL pour benchmark de flux
var tokenCorpus = []string{
	"SELECT\x00",
	"FROM\x00",
	"WHERE\x00",
	"INSERT\x00",
	"UPDATE\x00",
	"DELETE\x00",
}

func Benchmark_Scalar_Stream(b *testing.B) {
	totalBytes := int64(0)
	for _, s := range tokenCorpus {
		totalBytes += int64(len(s))
	}
	b.SetBytes(totalBytes)
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		for _, s := range tokenCorpus {
			_ = LexKeywordScalar(s)
		}
	}
}

func Benchmark_Vectorized_Stream(b *testing.B) {
	totalBytes := int64(0)
	for _, s := range tokenCorpus {
		totalBytes += int64(len(s))
	}
	b.SetBytes(totalBytes)
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		for _, s := range tokenCorpus {
			_ = LexKeyword(s)
		}
	}
}

func Benchmark_Scalar_Select(b *testing.B) {
	kw := "SELECT\x00"
	b.SetBytes(int64(len(kw)))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if LexKeywordScalar(kw) != TokSelect {
			b.Fatalf("échec")
		}
	}
}

func Benchmark_Vectorized_Select(b *testing.B) {
	kw := "SELECT\x00"
	b.SetBytes(int64(len(kw)))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if LexKeyword(kw) != TokSelect {
			b.Fatalf("échec")
		}
	}
}

func Benchmark_Scalar_Delete(b *testing.B) {
	kw := "DELETE\x00"
	b.SetBytes(int64(len(kw)))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if LexKeywordScalar(kw) != TokDelete {
			b.Fatalf("échec")
		}
	}
}

func Benchmark_Vectorized_Delete(b *testing.B) {
	kw := "DELETE\x00"
	b.SetBytes(int64(len(kw)))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if LexKeyword(kw) != TokDelete {
			b.Fatalf("échec")
		}
	}
}

func Benchmark_DirectBroadword_Select(b *testing.B) {
	kw := "SELECT\x00"
	b.SetBytes(int64(len(kw)))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		// Simule le chargement machine-word direct émis par un backend avec padding
		val := *(*uint32)(unsafe.Pointer(uintptr(unsafe.Pointer(unsafe.StringData(kw))) + 2))
		if val != 0x5443454c {
			b.Fatalf("échec")
		}
	}
}
