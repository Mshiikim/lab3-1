# Lab 3: Pantry on the Heap

## Pre-reqs

Clone this repo using Github Classroom.

```
cd /wherever/your/cloned/repo/is
cmake -B build -S .
cmake --build build  # or open the generated Visual Studio project
```

To run the program (unless using Visual Studio):
```
./build/Lab3
# or, on Windows:
.\build\Debug\Lab3.exe
```

## Description

Write a program that keeps an inventory of pantry items for cooking. These
ingredients will be stored in a text file that is specified on the command line
(you can hardcode it at first, e.g. "pantry.txt"). This file will be read from
to get the initial list as well as for storing any updates. The format of the
file will be a simple line-by-line where each line is the ingredient name
followed by the quantity. You can separate the ingredient name and quantity
with a tab character ('\t') or some other single character delimiter (like a
semicolon or comma).

When run, your program will display a menu like the following:

1. Add ingredient
2. Remove ingredient
3. Find ingredient
4. Edit ingredient
5. Display ingredients
6. Save
7. Quit

After displaying this menu, prompt the user for an option (i.e. a number). When
adding or changing an ingredient, remember to update or request the quantity of
the ingredient too.

To start with, try getting everything working without worrying about
quantities. You can add this feature after you get everything else working.

We have worked with code that appends to a list dynamically. Adding and
removing and finding (and even displaying) are all list actions. That is, they
don't technically have anything to do with ingredients. That means we will want
the following functions that modify a list on the heap:

- append (see previous lab)
- forEach
- find (or findIndex)
- remove
- update

You must write each of these functions to work with dynamic arrays of
c-strings. Some of this we will do in class.

If at any point you get stuck, try to work on one of these functions on its
own. We want to break down our problem into manageable chunks, and the best way
to do that is to think data-first. This means we want to think in terms of
lists and not ingredients, even though our list will be handling
ingredients.

## Requirements:

- Must use new / delete for the list and only allocate what is needed.
- Must accept the filename via a command line argument.
- Must use a lambda w/ forEach.
- Must use a lambda w/ find (or findIndex).

You can first write the program without all of these requirements, but you must
have all these things in order to get full marks.

As always, please let me know if you need help or are confused on anything.
