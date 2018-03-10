# Key-Aware
Offers keyboard aware text matching functions and data structures.

# Example

Typing `filr`, a typo of `file`.

A traditional fuzzy text matching function like [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance) simply counts the number of insertions, deletions, and subtitutions need to be made in order to turn a source word into a destination word. In this example, `filr` and `file` are of distance `1` from each other. Only the `r` needs to be substituted for an `e`.

Unfortunately, other words are also distance of `1` from `filr`, like `fill` and `film`. All of these words can be considered equal distance and equally likely to be the correct word. 

Looking at a keyboard, it becomes obvious which of the three is the closest match to the misspelled word. 

![Keyboard](/docs/keyboard_highlight_filr.png)

By asking not just "String Distance" but also physical distance, one can get a much more accurate answer for closet match.

![Sample](/docs/sample.png)


