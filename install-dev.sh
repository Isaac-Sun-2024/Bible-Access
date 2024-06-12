#!/bin/bash
git clone https://github.com/Isaac-Sun-2024/Bible-Access.git

cd Bible-Access
sudo mv kjv.tsv /usr/local/bin
gcc bible-is.c -o bible-kjv

cd output
sudo mv bible-kjv /usr/local/bin

echo 'YOU ARE DONE. GOOD JOB. - Isaac'
