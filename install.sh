#!/bin/bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
mkdir isaac
brew install git
git clone https://github.com/Isaac-Sun-2024/Bible-Access.git

brew install gcc
gcc --version

sudo mv kjv.tsv /usr/local/bin
sudo gcc bible-is.c -o bible-kjv

sudo mv bible-kjv /usr/local/bin

echo '(Black screen with text; The sound of buzzing bees can be heard)
According to all known laws
of aviation,
there is no way a bee
should be able to fly.
Its wings are too small to get
its fat little body off the ground. - Isaac'
