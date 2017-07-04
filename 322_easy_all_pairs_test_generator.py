# https://www.reddit.com/r/dailyprogrammer/comments/6l3hd8/20170703_challenge_322_easy_all_pairs_test/djr0jsx/

import itertools
import pprint

#input = [['0', '1'], ['A', 'B', 'C'], ['D', 'E', 'F', 'G']]
#input = [['0', '1', '2', '3'], ['A', 'B', 'C', 'D'], ['E', 'F', 'G', 'H', 'I']]
input = [['0', '1', '2', '3', '4'], ['A', 'B', 'C', 'D', 'E'], ['F', 'G', 'H', 'I'], ['J', 'K', 'L']]

pair_dict = dict()
final_results = []

#for min_unique in range(len(input), 0, -1):
for min_unique in range(6, 0, -1):
    for k in itertools.product(*input):
        save = False
        unique_count = 0
        temp_dict = dict()
        # TODO: get rid of temp_dict somehow? maybe by leveraging the values in pair_dict?
        # TODO: cull records with zero unique permutations, so they aren't examined on subsequent runs?
        for n in itertools.permutations(k, 2):
            n = frozenset(n)
            if n not in temp_dict and n not in pair_dict:
                unique_count += 1
                temp_dict[n] = None
                if unique_count >= min_unique:
                    save = True
        #print k, unique_count, "unique. min is", min_unique, "- save is", save
        if save:
            final_results.append(k)
            temp_dict = pair_dict = dict(pair_dict.items() + temp_dict.items())


pp = pprint.PrettyPrinter(indent=4)
pp.pprint(final_results)
print len(final_results)
