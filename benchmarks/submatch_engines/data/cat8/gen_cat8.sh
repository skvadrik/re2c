#!/bin/bash

# quick and dirty
> big
for i in {1..460}; do cat small >> temp ; done
for i in {1..400}; do cat temp >> big ; done
rm temp
