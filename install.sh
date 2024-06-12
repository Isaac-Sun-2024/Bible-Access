#!/bin/bash
curl https://raw.githubusercontent.com/Isaac-Sun-2024/Bible-Access/main/kjv.tsv
curl https://raw.githubusercontent.com/Isaac-Sun-2024/Bible-Access/main/bible-is.c

mkdir isaac
brew install gcc
gcc --version

sudo mv kjv.tsv /usr/local/bin
sudo mv bible-is.c isaac
sudo gcc bible-is.c -o bible-kjv

cd isaac/output
sudo mv bible-kjv /usr/local/bin
