# https://www.reddit.com/r/dailyprogrammer/comments/5seexn/20170206_challenge_302_easy_spelling_with/
# First, load the element list as a dictionary. As we're doing that, create a field delimiter string of all of the element symbols.
# Second, apply the field delimiter string to each input word and map back to the dictionary.
# executed with "gawk -fchemistry_challenge.awk ptdata2.csv"

BEGIN {
    FS=","
    NEW_FS=","
}

{
    element_dict[tolower($2)] = $2"|"$3
    NEW_FS = tolower($2)"|"NEW_FS
}

END {
    while (getline < "input.txt")
    {
        final_word = ""
        final_list = ""
        element_count = split($0, a, NEW_FS, b)

        for (i = 1; i <= element_count; i++)
        {
            split(element_dict[b[i]], a, "|")
            final_word = final_word""a[1]
            final_list = final_list" "a[2]
        }
        printf("%s (%s)\n", final_word, final_list)
    }