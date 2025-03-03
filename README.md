## Hamiltonian Snake: a snake ai in c++ 

- Perturbated Hamiltonian Cycle: https://johnflux.com/2015/05/02/nokia-6110-part-3-algorithms/


****

### Build

- **Dep**: `sudo apt-get update && sudo apt-get install g++ cmake libsfml-dev`  
- **Run**: `cd bin/ && ./build.sh -R && ./compile.sh && ./run.sh -M phc -S small`  

```
usage: apps/exec [-h] [-M MODE] [-S SIZE]

CNAKE++AI

optional args:
  -h       show this help message and exit
  -M MODE  set mode  < phc | hc | play >
  -S SIZE  set size  < small | large >

optional cmds:
  key S    set speed 24FPS, VSYNC, MAX
  key D    set debug NO, YES
```

****

### Demo

![Demo small png](demo/demo_small.png)  

![Demo large png](demo/demo_large.png)  
