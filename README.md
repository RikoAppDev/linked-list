# Linked List of Structures in C

## Overview
This project features a C program that manages and processes records using a dynamic linked list. The records, derived from a measurement module, are stored in a file named `dataloger_V2.txt`. Each record in the file is separated by `$$$` markers for clarity, with each record attribute placed on a separate line.

## Record Structure
- **ID_cislo_mer_osoby**: Ten-digit integer divisible by 11
- **Meno_osoby**: String (max. 30 characters)
- **Mer_modul**: Capital letter from `A` to `Z` followed by a two-digit number
- **Typ_mer_veliciny**: Two characters from `{R1, U1, A1, R2, U2, A2, R4, U4, A4}`
- **Hodnota**: Real number
- **Cas_merania**: Four characters (hours and minutes)
- **Datum**: Eight-digit integer in the form `rrrrmmdd`

## Commands
- **`n`**: Loads records from `dataloger_V2.txt` into a linked list. Outputs the number of loaded records or an error message if the file cannot be opened.
- **`v`**: Displays the entire linked list with each record numbered sequentially. If the list is empty, no output is generated.
- **`s`**: Deletes records by `ID_cislo_mer_osoby` and outputs the number of deleted records or an error message if the list is not created.
- **`p`**: Adds a record to the linked list at a specified position. If the position does not exist, the record is added to the end of the list.
- **`h`**: Searches for and displays records based on `Mer_modul`. Outputs the records or a message if no matching records are found.
- **`r`**: Swaps two records in the linked list by their positions. No output is generated if the positions do not exist.
- **`k`**: Ends the program, deallocating memory and closing files.

## Dynamic List Management
- The program ensures efficient memory use by dynamically allocating and freeing memory as records are added or removed.
- Proper memory management is implemented to avoid leaks and ensure the stability of the program.
