# ProjectBahamut2 - C++ OpenGL Game Engine
ProjectBahamut is a temporary name for my game engine.  
The engine uses C++ with OpenGL, SDL2, glad, stb_image, GLM, ASSIMP, imgui, and yaml-cpp.  

---
The engine is a work in progress, but you can check the progress on my [blog](https://Kirugaming.com/blog).  
There is also a basic roadmap that I will update occasionally on this [Github repositories wiki](https://github.com/Kirugaming/ProjectBahamut2/wiki).  
I plan to keep working on this project so check back regularly.  
## Screenshots:
![](https://cdn.discordapp.com/attachments/457750512683450371/1164784544491245599/image.png?ex=65447924&is=65320424&hm=d5828ca7dda4be342296d647e102f624c4233a812173f9478b9560e546517d86&)  
![](https://cdn.discordapp.com/attachments/694978568907784254/1147365972458623006/devgif12.gif)
How level files are formatted:
---
The level files currently use YAML.  
This is an example of a level file:  
```YAML
GameObjects:
  - name: Raphtalia
    model: raph/raph.obj # path from executable
    position:
      - 0.0 # x
      - 0.0 # y
      - 0.0 # z
    rotation:
      - 0.0 # x (pitch)
      - 0.0 # y (yaw)
      - 0.0 # z (roll)
    scale:
      - 1.0 # x
      - 1.0 # y
      - 1.0 # z
```
