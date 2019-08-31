# About this repository 
[![All Contributors](https://img.shields.io/badge/all_contributors-1-orange.svg?style=flat-square)](#contributors)

Just for your understanding this is a repository with its sole purpose to have log and updates from CDD (Comunicación de 
Datos) assignment at Metropolitan University of Technology (a.k.a. UTEM), Chile. Our professor [Sebastian Salazar] (https://github.com/sebasalazar) 
is responsible for the assignment and the grading of those school assignment

## Folder Organization

    .
    ├── ...
    ├── NewtonRaphson           # Newton Raphson method to solve f(x) polynomial roots
    ├── README.md               # Tbis Readme.md
    └── ...


## Pre requisites

We're working under this enviroment and languages conventions 

Requirement  | Version
------------- | -------------
[Ubuntu](https://ubuntu.com/download/desktop)    |  18.04 LTS 64 bits 
[C++](https://isocpp.org/)       |  std = 11 
[GCC](https://gcc.gnu.org/)       |  7.4.0 
[cppcheck](https://github.com/danmar/cppcheck)  |  1.82 
[make](https://www.gnu.org/software/make/)      |  4.1 
[cmake](https://cmake.org/)     |  3.10.2

So in under to make sure that our code will work under your environment you have to install those versions first (if you don't have the utilities).

If you want to check our code, please check it as you like. Here you can find a command line input to use cppcheck:

```
$ cppcheck --enable=all  --suppress=missingIncludeSystem programa.cpp 2>err.txt
```
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/albertosaurio"><img src="https://avatars2.githubusercontent.com/u/39352812?v=4" width="100px;" alt="albertosaurio"/><br /><sub><b>albertosaurio</b></sub></a><br /><a href="https://github.com/Nicolasipr/CDD/commits?author=albertosaurio" title="Code">💻</a> <a href="#ideas-albertosaurio" title="Ideas, Planning, & Feedback">🤔</a></td>
  </tr>
</table>

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!