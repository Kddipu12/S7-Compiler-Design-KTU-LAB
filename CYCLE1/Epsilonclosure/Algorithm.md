
### Algorithm

1. **Initialize Variables**
    - Read the number of alphabets and store them in `alphabet`.
    - Read the number of states and transitions.
    - Initialize the transition table with NULL.

2. **Insert Transitions**
    - For each transition, find the index of the alphabet.
    - Insert the transition into the linked list at the appropriate position in the transition table.

3. **Compute Epsilon Closure**
    - For each state, initialize `buffer` and `e_closure`.
    - Call `findclosure()` to recursively compute the epsilon closure.
    - Store the result in `e_closure` and print it using `print_e_closure()`.

This code systematically reads inputs, stores transitions, and computes the epsilon closures for all states in an NFA with epsilon transitions.
