#!/bin/bash
cd ~/
mkdir isaac
brew install git
git clone https://github.com/Isaac-Sun-2024/Bible-Access.git

brew install gcc
gcc --version

sudo mv kjv.tsv /usr/local/bin
sudo gcc bible-is.c -o bible-kjv

sudo mv bible-kjv /usr/local/bin
