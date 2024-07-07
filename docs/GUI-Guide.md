# Zappy - GUI Guide

The GUI is the graphical user interface of the game. Its goal is to represent the game world and the players in a visual way. It is controlled by the server, which sends it information about the game state and the players. The GUI then interprets this information and displays it to the user. The GUI is also able to send commands to the server to request information and adjust the speed of the game.

## Communication

Just like with the AI, the GUI and server communicate using a TCP connection. Messages text is sent through the socket and terminated by a newline character. 

When connecting to the server, the GUI will receive a welcome message. It will then have to send `GRAPHIC` to the server to identify itself as a GUI. The server will then register this connection as a GUI and start sending/recieving information about the game state.

Example of communication:
```
SERVER: WELCOME
GUI:    GRAPHIC
```

## Commands / Events

Everything that the server sends to the GUI is called an event. Almost all events are sent automatically at some point in the connection, some of the events can be directly requested by the GUI. The following table lists all the events that the GUI can receive from the server:

| Event Details                   | Server message                                                    | Request command |
|---------------------------------|-------------------------------------------------------------------|-----------------|
| Map size                        | `msz` X Y                                                         | `msz`           |
| Content of a tile               | `bct` X Y q0 q1 q2 q3 q4 q5 q6                                    | `bct` X Y       |
| Content of all tiles            | `bct` X Y q0 q1 q2 q3 q4 q5 q6 `bct` X Y q0 q1 q2 q3 q4 q5 q6 ... | `mct`           |
| Name of all teams               | `tna` N `tna` N ...                                               | `tna`           |
| New player                      | `pnw` n X Y O L N                                                 | N/A             |
| Player's position               | `ppo` n X Y O                                                     | `ppo` n         |
| Player's level                  | `plv` n L                                                         | `plv` n         |
| Player's inventory              | `pin` n X Y q0 q1 q2 q3 q4 q5 q6                                  | `pin` n         |
| Ejection                        | `pex` n                                                           | N/A             |
| Broadcast                       | `pbc` n M                                                         | N/A             |
| Incantation start               | `pic` X Y L n n ...                                               | N/A             |
| Incantation end                 | `pie` X Y R                                                       | N/A             |
| Fork start                      | `pfk` n                                                           | N/A             |
| Ressource dropped               | `pdr` n i                                                         | N/A             |
| Ressource collected             | `pgt` n i                                                         | N/A             |
| Player's death                  | `pdi` n                                                           | N/A             |
| Team slot created               | `enw` e n X Y                                                     | N/A             |
| Player's connection from a slot | `ebo` e                                                           | N/A             |
| Team slot destroyed             | `edi` e                                                           | N/A             |
| Current time unit               | `sgt` T                                                           | `sgt`           |
| Time unit modified              | `sst` T                                                           | `sst` T         |
| Game end                        | `seg` N                                                           | N/A             |
| Message from the server         | `smg` M                                                           | N/A             |
| Unknown command                 | `suc`                                                             | N/A             |
| Bad command parameters          | `sbp`                                                             | N/A             |

**Legend**:

| Symbol | Meaning                                        |
|--------|------------------------------------------------|
| X      | Width or horizontal position                   |
| Y      | Height or vertical position                    |
| q0     | Food quantity                                  |
| q1     | Linemate quantity                              |
| q2     | Deraumere quantity                             |
| q3     | Sibur quantity                                 |
| q4     | Mendiane quantity                              |
| q5     | Phiras quantity                                |
| q6     | Thystame quantity                              |
| n      | Player number                                  |
| O      | Orientation: 1(UP), 2(DOWN), 3(RIGHT), 4(LEFT) |
| L      | Player/incantation level                       |
| e      | Egg number                                     |
| T      | Time unit                                      |
| N      | Team name                                      |
| R      | Incantation result                             |
| M      | Message                                        |
| i      | Ressource number (q**N**)                      |

---
<- [Back to README](../README.md)