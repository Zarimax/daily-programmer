# https://www.reddit.com/r/dailyprogrammer/comments/6l3hd8/20170703_challenge_322_easy_all_pairs_test/djr0jsx/

from itertools import product, combinations
from pprint import PrettyPrinter
from timeit import default_timer as timer

test_1 = [['0', '1'], ['A', 'B', 'C'], ['D', 'E', 'F', 'G']]
test_2 = [['0', '1', '2', '3'], ['A', 'B', 'C', 'D'], ['E', 'F', 'G', 'H', 'I']]
test_3 = [['0', '1', '2', '3', '4'], ['A', 'B', 'C', 'D', 'E'], ['F', 'G', 'H', 'I'], ['J', 'K', 'L']]

def all_pairs_test(input):
    # ------------- start timer -------------
    start = timer()
    pair_dict = dict()
    final_results = []
    for min_unique in range(len(input)+1, 0, -1): #TODO: why does "for min_unique in range(10, 0, -1):" return 30?
        for k in product(*input):
            save = False
            unique_count = 0
            temp_dict = dict()
            # TODO: get rid of temp_dict somehow? maybe by leveraging the values in pair_dict?
            # TODO: cull records with zero unique permutations, so they aren't examined on subsequent runs?
            for n in combinations(k, 2):
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
    end = timer()
    # ------------- end timer -------------
    # TODO: validate that final_results contains all possible permutations
    pp = PrettyPrinter(indent=4)
    pp.pprint(final_results)
    print "number of sets:", len(final_results)
    print "speed factor:", (end - start)*1000.00

all_pairs_test(test_1)
all_pairs_test(test_2)
all_pairs_test(test_3)
