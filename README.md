# Introduction to Computer Science (CS50)

[![Open Source Society University - Computer Science](https://img.shields.io/badge/OSSU-computer--science-blue.svg)](https://github.com/open-source-society/computer-science)

Projects and problem sets from Harvard's Introduction to Computer Science (CS50).

Following the [Open Source Society Computer Science curriculum](https://github.com/open-source-society/computer-science).

## Installing Dependencies
### Ubuntu

* `clang` to compile as the CS50 IDE does
```bash
$ sudo apt install clang
```
* `Valgrind` to test for memory leaks
```bash
$ sudo apt install valgrind
```
* `astyle` to support `style50`
```bash
$ sudo add-apt-repository ppa:cs50/ppa
$ sudo apt-get update
$ sudo apt-get install astyle
```
* `sqlite3` to connect to databases
```bash
$ sudo apt install sqlite3
```

### MacOSX

```bash
$ brew bundle
```

> **Note** If you are using the new Apple Silicon chips:
>
> Homebrew will skip valgrind, as no bottle yet exists for that chip architecture.
> Valgrind tests will, of course, fail.

### IEX API Key

To run pset9, you'll need an API key for IEX Cloud Services.

1. Visit iexcloud.io/cloud-login#/register/.
2. Select the "Individual" account type, then enter your email address and a password, and click "Create account."
3. Once registered, scroll down to "Get started for free" and click "Select Start" to choose the free plan.
4. Once you've confirmed your account via a confirmation email, visit https://iexcloud.io/console/tokens.
5. Copy the key that appears under the Token column (it should begin with pk_).
6. In the `.env` file, fill in the `API_KEY` variable with your key's value.
7. Profit.

## [Problem Set 1](https://github.com/walshification/cs50/tree/master/pset1)
* [hello](https://github.com/walshification/cs50/tree/master/pset1/hello.c)
* [mario](https://github.com/walshification/cs50/tree/master/pset1/mario.c)
* [water](https://github.com/walshification/cs50/tree/master/pset1/water.c)
* [greedy](https://github.com/walshification/cs50/tree/master/pset1/greedy.c)

## [Problem Set 2](https://github.com/walshification/cs50/tree/master/pset2)
* [initials](https://github.com/walshification/cs50/tree/master/pset2/initials.c)
* [caesar](https://github.com/walshification/cs50/tree/master/pset2/caesar.c)
* [vigenere](https://github.com/walshification/cs50/tree/master/pset2/vigenere.c)
