# Pong UDP multi-player game



## Folder Organization

    .
    ├── ...
    ├── server          # files containing server setup 
    ├── client          # Files containing client udp access to server
    ├── game            # where the game resides: classes, functions, handlers and headers 
    ├── README.md               # This Readme.md
    └── ...

## To be completed

About Folder and Organization:
- [x] Folder structure
- [x] Creating Menu 
- [x] Creating About
- [x] Section where you can modify game options 

Regarding Game functionality:
- [x] Displaying Board
- [x] Displaying Player's name and score
- [x] Creating a ball
- [x] Wall Collisions 
- [x] Reseting ball each time a player scores
- [ ] Player's Paddle Collision
- [ ] Sending Paddle Y Position to server
- [ ] Player Key event handler
- [ ] Setting up match: Best of three sets, Casual-mode & more (hopefully)... 

## How it works
 
### Network Modelling
 
 The fundamental part of this project is the network model. Since the goal of this program is to 
 code a client-server network modelling, peer-to-peer is clearly not an option (even though we were not 
 choosing it anyways, because it doesn't scale well). 
 
 Regarding about how much the client trust the client, there's some approaches such as sending client inputs 
 to the server, but one disadvantage is that client can easily use some kind of cheats. The second approach is 
 telling that some client K is somewhere over the game, doing something (We have selected this one).
 
### Synchronization 
 About synchronization, there's some ways to handle this situation...
 
 Snapshot Sync
 
 State Sync 
 
 Deterministic Lockstep
 
### Sockets

#### TCP 

#### UDP 

### Game Design
 
 