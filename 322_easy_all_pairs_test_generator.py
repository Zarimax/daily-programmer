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
    pair_dict = dict()  #track which pairs have been seen
    test_dict = dict()  #track all pairs, (for future validation)
    final_results = []  #track all saved sets. the goal is to minimize the number of these
    
    #minimize the number of saved sets by selecting sets with the greatest number of new pairs
    for unique_count_threshold in range(len(input)+1, 0, -1): #voodoo in selecting these range bounds
        for k in product(*input):
            save = False
            unique_count = 0
            temp_dict = dict() #track which pairs have been seen for this permutation only
            for n in combinations(k, 2):
                n = frozenset(n)
                test_dict[n] = None
                if n not in temp_dict and n not in pair_dict:
                    unique_count += 1   #we found a unique pair
                    temp_dict[n] = None #save it in this permutation's dict
                    save = unique_count >= unique_count_threshold
            #print k, unique_count, "unique. min is", unique_count_threshold, "- save is", save
            if save:
                final_results.append(k)
                # merge temp_dict into pair_dict, (since we're saving this set)
                temp_dict = pair_dict = dict(pair_dict.items() + temp_dict.items())
    end = timer()
    # ------------- end timer -------------

    # display results and perform validation tests
    print "================================"
    pp = PrettyPrinter(indent=4)
    pp.pprint(final_results)

    # validate that final_results contains all possible permutations
    for x in test_dict:
        found = False
        for y in final_results:
            if list(x)[0] in y and list(x)[1] in y:
                found = True
        if not found:
            print "*** ERROR: failed to confirm pair", x

    # validate that pair_dict contains all the combinations that it should
    diff = len(test_dict) - len(pair_dict)
    if diff != 0:
        print "*** ERROR: pair_dict and test_dict do not match", diff, "pairs have been missed!"

    print "run time:", end - start
    print "number of sets:", len(final_results)

# ------------- start execution here -------------
all_pairs_test(test_1)
all_pairs_test(test_2)
all_pairs_test(test_3)
