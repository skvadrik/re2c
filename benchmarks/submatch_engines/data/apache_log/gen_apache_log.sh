#!/bin/bash

# quick and dirty
> big
for i in {1..20}; do cat small >> temp ; done
for i in {1..30}; do cat temp >> big ; done
rm temp
