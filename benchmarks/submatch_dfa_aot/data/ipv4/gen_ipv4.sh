#!/bin/bash

# quick and dirty
> big
for i in {1..1000}; do cat small >> temp ; done
for i in {1..1000}; do cat temp >> big ; done
rm temp
