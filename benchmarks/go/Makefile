.DEFAULT_GOAL := check
RE2GO ?= ../../build/re2go

.PHONY: generate check smoke clean
generate:
	python3 ../_scripts/gen_linear.py --re2go "$(RE2GO)" --out generated

generated/fixtures.json:
	python3 ../_scripts/gen_linear.py --re2go "$(RE2GO)" --out generated

check: generated/fixtures.json
	go test -count=1 ./...

smoke: generated/fixtures.json
	go test -run '^$$' -bench . -benchtime=1x -count=1 ./...

clean:
	rm -f generated/*.go generated/*.re generated/*.json
	rmdir generated 2>/dev/null || true
