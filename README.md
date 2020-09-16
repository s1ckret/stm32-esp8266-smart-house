
# stm32-esp12f-smart-house
Smart house student project on stm32 and esp12f

## Project structure
The project consists of
 - server
 - webpage (i.e. Web Control Panel)
 - embedded (i.e. Stm32 project)
 - client-emulator _(for testing purposes)_

## How to build and run
Firstly, clone the repo!
```
git clone https://github.com/LazyPride/stm32-esp12f-smart-house.git
```

or with ssh
```
git clone git@github.com:LazyPride/stm32-esp12f-smart-house.git
```

Enter in the `stm32-esp12f-smart-house` folder.
```
cd ./stm32-esp12f-smart-house
```

### How to build and run the server

You need `python3` to be installed on your PC. Go to the official website and download installer if you have Windows. It is necessary to install `pip` and add python3 to the PATH.
```
# On Ubuntu
sudo apt install python3
```

Then execute next commands:
```
cd ./server
python3 ./server.py
```

> Note: if you don't have the necessary python libs install them with pip!
```
# On Ubuntu
sudo apt install python3-pip
# Ubuntu/Windows
sudo pip3 install <library-name>
```

### How to build and run the stm32 project
You need STM32CubeIDE to be installed on your PC.
After installing I advice to to set black theme fol;owing [this tutorial](https://www.youtube.com/watch?v=XdXj0za2diY&ab_channel=Simplech)
The next step is getting rid of tabs!

1. Open STM32CubeIDE
2. Go to _Window_ -> _Preferences_
3. Go to _General_ -> _Editor_ -> _Text Editors_
  3.1. Set `Displayed tab width` to 2
  3.2. Mark `Insert spaces for tabs`
4. Go to _C/C++_ -> _Code Style_ -> _Formatter_
  4.1. Click `New...`
  4.2. Name it as you wish (Ex: "NoTabs")
  4.3. Hit `OK`
  4.4. In the popup window set `Tab policy` to `Spaces only`
  4.5. Set `Indentation size` to 2
  4.6. Set `Tab size` to 2
  4.7. Hit `Apply`, `OK`