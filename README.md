PicoVaders
==========

A Space Invaders inspired shoot-em-up game for the RP2040-based 
[PicoSystem](https://shop.pimoroni.com/products/picosystem). Shoot aliens. 
Save mankind.

This game is released under the MIT License; see LICENSE for details.

Image assets need to be converted for use with the PicoSystem SDK; I've ended
up building my [own tools](https://github.com/ahnlak/pstools) so that it directly
generates code I can link / include into the project. The 1-bit logo needs a
more manual approach, so ... err ... don't change it?

To build, you will need to tell CMake where to find the 
[PicoSystem SDK](https://github.com/pimoroni/picosystem):

`cmake -DPICOSYSTEM_DIR=<picosystem directory> ..`

(where `<picosystem directory>` is wherever you cloned the SDK into)

```
Share & Enjoy
```