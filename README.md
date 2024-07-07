# Zappy

The Zappy is a game where several teams confront each others on a map with the goal of collecting ressources and evolve.

The goal of the game is to be the first team to have 6 player reach the highest level.
This is done through collecting food to avoid dying and stones that are required for elevation, the ritual that allows players to increase their level.

The game is played through the network, each players connecting to the main server (`zappy_server`) of the game and choosing their team.
The players themselves are not human-controlled, but instead controlled by an AI (`zappy_ai`).

Also controlled through the network, is a Graphical user interface (`zappy_gui`), that communicate with the server using a special set of commands.

### Dependencies

- [CMake](https://cmake.org/)
- [GNU Compiler Collection](https://gcc.gnu.org/)
- [GNU Make](https://www.gnu.org/software/make/)
- [Python3](https://www.python.org/)
- [SFML](https://www.sfml-dev.org/)
- [Criterion](https://github.com/Snaipe/Criterion) (for unit tests)

### Building

You can build the 3 executables using the provided Makefile:

```sh
make
```

Additionally, you can build each executable separately using the appropriately named rules:

```sh
make zappy_server
make zappy_gui
make zappy_ai
```

### Usage

Once built, each executable can be run using the following flags (use `-help` for more information on each mandatory/optional flags):

```
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq -d
```
```
USAGE: ./zappy_gui -p port -h machine -g graphics
```
```
USAGE: ./zappy_ai -p port -n name -h machine -d
```

### Development and docs

For developers who wish to implement their own AI/GUI the following documentation files explain in details how to implement each program and how to abide by their respective communication protocol:

- [AI Documentation](docs/AI-Guide.md)
- [GUI Documentation](docs/GUI-Guide.md)

While working on this project's source code (or any of its in-house libraries), you can launch its unit tests using the following makefile rule (requires [Criterion](https://github.com/Snaipe/Criterion)):

```sh
make tests_run
```

### Contributors

[<img src="https://avatars.githubusercontent.com/u/84138824?v=4" width="75"/>](https://github.com/alexishachemi)
[<img src="https://avatars.githubusercontent.com/u/67485955?v=4" width="75"/>](https://github.com/Kuawhrime)
[<img src="https://avatars.githubusercontent.com/u/103694544?v=4" width="75"/>](https://github.com/martin-vergues)
[<img src="https://avatars.githubusercontent.com/u/114906179?v=4" width="75"/>](https://github.com/DarkWhige)
[<img src="https://avatars.githubusercontent.com/u/114910458?v=4" width="75"/>](https://github.com/jauguet)
[<img src="https://avatars.githubusercontent.com/u/114911283?v=4" width="75"/>](https://github.com/manal67)

### Contact

For any questions/help about this project, please contact the following contributors depending on the subject:

**Server**: [Alexis Hachemi](https://github.com/alexishachemi) at alexis.hachemi@epitech.eu

**GUI**: [Karim Mohamed](https://github.com/Kuawhrime) at karim.mohamed@epitech.eu

**AI**: [Martin Vergues](https://github.com/martin-vergues) at martin.vergues@epitech.eu
