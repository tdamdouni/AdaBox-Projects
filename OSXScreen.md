## Installing GNU Screen on OS X in Homebrew

I want to edit in one tab, run what I edit in the other. Typical multi-view stuff. I've used Terminal.app for the last few years. Lately, however, after not long enough, Terminal gets laggy when I switch between tabs.

The stutter between edit and run is annoying, an unnacceptable. One of the major reason I've chosen to work with character based UI is because it is snappy. There shouldn't be a lag while a screen of UTF-8 is rendered in a monospace font.

The lag gets progressively longer, chipping at my productivity with irritation. The only solution is to kill all my Terminals, which essentially kills my flow. Terminal.app won't remember where I was for me. I have to initialize ever tab.

## GNU Screen

Back in the day I'd use GNU Screen. GNU Screen gives you different windows that you use keyboard commands to alternate between, but in a single terminal window.

I can't remember all that I did with it, but I developed a lot of muscle memory around it.

There was a lot more to learn about GNU Screen that I didn't learn. You can navigate your scrollback buffer from the keyboard, cutting and pasting. You can detach screen, close your terminal, then open a new terminal and reattach. Screen will be as you left it.

I'd much rather develop muscle memory that I can take with me to Linux. The only thing that Terminal.app gives me is tabs. Screen gives me tabs, keyboard scrollback, split windows, and saved detached sessions.

## 256 Colors

Sadly, I found that the `screen` that comes with OS X does not support 256 colors. Starting with this article [GNU/Screen with 256 colours in Mac OS X](http://ryanwilliams.org/2010/Oct/09/gnu-screen-256-colours-mac-os-x), I built GNU Screen as follows.

```
git clone git clone git://git.savannah.gnu.org/screen.git
cd screen/src
mkdir -p /opt/etc
mv etc/etcscreenrc /opt/etc/screenrc
./autogen.sh
./configure --prefix=/opt/Cellar/screen/3.6.0  --enable-colors256 --with-sys-screenrc=/opt/etc/screenrc
make
make install
brew link screen
```

Now I can run screen and see that I have 265 colors.