# reasults on searching good CSS codes

n=20, G_x_row=9, G_z_row=9, d=[2,5],[4,2]
n=22,         9          9    [4,3]
  22          10         10   [3,5]


Renyu's example:
n0=11  [ 0, 3 ] [0,1]   n=22 dX=4 dZ=5 d0=4

# how-to-use-weilei-lib
A sample repo on how to use functions in weilei_lib. One can fork this one and use it as a starting point


# How to use from this repo

I use weilei_lib as a submodule here. It works like two repo, but just one inside the other. One should commit changes independently. To clone it, use the following cmd.
```
git clone --recurse-submodules https://github.com/QEC-pages/how-to-use-weilei-lib
```
You can test it by
```
make test_lib
make test
```




# info on sub module

see https://git-scm.com/book/en/v2/Git-Tools-Submodules

init:
```
git submodule add git@github.com:WeileiZeng/weilei_lib.git
```
You can also use http instead of ssh

Then you work on those like two different repo.


## simulation report

table of CSS codes

    n=9:        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=10:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=11:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=12:       [0, 0, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=13:       [0, 0, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=14:       [0, 0, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=15:       [0, 0, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=16:       [0, 0, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=17:       [0, 0, 4, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=18:       [0, 0, 4, 3, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=19:       [0, 0, 4, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=20:       [0, 0, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0]
    n=21:       [0, 0, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0]
    n=22:       [0, 0, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0]
    n=23:       [0, 0, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0]
    n=24:       [0, 0, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0]
    n=25:       [0, 0, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0]
    n=26:       [0, 0, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0]
    n=27:       [0, 0, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0]
    n=28:       [0, 0, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 0]
    n=29:       [0, 0, 5, 5, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2]
    n=30:       [0, 0, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2]
    n=31:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=32:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=33:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    n=34:       [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]