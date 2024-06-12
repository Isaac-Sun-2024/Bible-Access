#!/bin/bash
curl https://raw.githubusercontent.com/Isaac-Sun-2024/Bible-Access/main/kjv.tsv
curl https://raw.githubusercontent.com/Isaac-Sun-2024/Bible-Access/main/bible-is.c

mkdir isaac
brew install gcc
gcc --version

mv kjv.tsv /usr/local/bin
mv bible-is.c isaac
gcc bible-is.c -o bible

cd isaac/output
mv bible /usr/local/bin