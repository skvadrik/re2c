#!/bin/bash

# quick and dirty
> big
for i in {1..200}; do cat small >> temp ; done
for i in {1..150}; do cat temp >> big ; done
rm temp
