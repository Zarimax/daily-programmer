import itertools
import pprint

input = [['0', '1'], ['A', 'B', 'C'], ['D', 'E', 'F', 'G']]
#input = [['0', '1', '2', '3'], ['A', 'B', 'C', 'D'], ['E', 'F', 'G', 'H', 'I']]
#input = [['0', '1', '2', '3', '4'], ['A', 'B', 'C', 'D', 'E'], ['F', 'G', 'H', 'I'], ['J', 'K', 'L']]
#input = [['0', '1', '2', '3', '4'], ['A', 'B', 'C', 'D', 'E'], ['F', 'G', 'H', 'I'], ['J', 'K', 'L'], ['X', 'Y', 'Z']]

pair_dict = dict()
final_results = []

def do_scan(min_unique):
    global pair_dict
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
        print k, unique_count, "unique. min is", min_unique, "- save is", save
        if save:
            final_results.append(k)
            temp_dict = pair_dict = dict(pair_dict.items() + temp_dict.items())

# TODO: drive range dynamically based on input list?
for i in range(6, 0, -1):
    do_scan(i)

pp = pprint.PrettyPrinter(indent=4)
pp.pprint(final_results)
print len(final_results)
