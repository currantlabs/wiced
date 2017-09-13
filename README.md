# wiced
Temporary playground for working with the BCM9WCD9EVAL1 dev-board (uses the BCM94343WWCD1 module)

## About
We're currently at work on extending the 'new-day' repo to support both the
existing Wallace hardware, as well as the new BCM94343 module based
Stringer hardware. The stuff I'm playing with here will ultimately be
subsumed in 'new-day' but I'm pushing it up there just so we can kick the
tires a bit.

In this repo, I'm playing with ideas on how best to bolt the compilation of
source files common to both Wallace and Stringer onto the back of the
standard WICED SDK build system. 

## Usage 
Be sure to `git clone --recursive` this project to pick up the WICED SDK
(version "WICED-SDK-3.7.0-7").

