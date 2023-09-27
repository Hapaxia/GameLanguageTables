# GameLanguageTables

## Introduction
GLT (Game Language Tables) is a collection of tables of strings (words/phrases) in multiple languages used for games by game developers.

## Usage
The tables are in markdown and should be quite easy to parse if you would like to.

[Some C++ parsers are provided](Parsers) if you'd like to use those but feel free to use your own.

- The [ParseToStringVectors](https://github.com/Hapaxia/GameLanguageTables/blob/main/Parsers/ParseToStringVectors.cpp) parser will create a vector (words/phrases) of vector (language) of strings that include all of the words and phrases of all the languages.
- The [ParseToLingo](https://github.com/Hapaxia/GameLanguageTables/blob/main/Parsers/ParseToLingo.cpp) parser will add all of the strings for all languages to the [Lingo](https://github.com/Hapaxia/Lingo) object.

You can also just used the table to reference certain words/phrases in multiple languages or simply copy and paste it to wherever you need it.

## Expansion
If you would like to see more strings, groups of strings, or other languages, feel free to let me know or contribute.

## Improvement
If you are a native/fluent speaker of a language that is included and you would like to correct the entries, you can let me know or contribute.

## Contribution
If you would like to contribute to GLT, you are very welcome!

Please, first, open an issue.
We can discuss and clarify the addition/correction, if necessary.

If you would like to make the modification yourself, create a pull request.
> Note: be careful to keep the table format as well as keeping the columns lined up as well as possible (not including the horizontal line row or the final empty row).  
> The empty row can be used to copy for a new row if a new word/phrase is being added.

