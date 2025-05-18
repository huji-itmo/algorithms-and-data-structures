1444. Elephpotamus
Time limit: 0.5 second
Memory limit: 64 MB
Harry Potter is taking an examination in Care for Magical Creatures. His task is to feed a dwarf elephpotamus. Harry remembers that elephpotamuses are very straightforward and imperturbable. In fact, they are so straightforward that always move along a straight line and they are so imperturbable that only move when attracted by something really tasty. In addition, if an elephpotamus stumbles into a chain of its own footprints, it falls into a stupor and refuses to go anywhere. According to Hagrid, elephpotamuses usually get back home moving along their footprints. This is why they never cross them, otherwise they may get lost. When an elephpotamus sees its footprints, it tries to remember in detail all its movements since leaving home (this is also the reason why they move along straight lines only, this way it is easier to memorize). Basing on this information, the animal calculates in which direction its burrow is situated, then turns and goes straight to it. It takes some (rather large) time for an elephpotamus to perform these calculations. And what some ignoramuses recognize as a stupor is in fact a demonstration of outstanding calculating abilities of this wonderful, though a bit slow-witted creature.
Elephpotamuses' favorite dainty is elephant pumpkins, and some of such pumpkins grow on the lawn where Harry is to take his exam. At the start of the exam, Hagrid will drag the elephpotamus to one of the pumpkins. Having fed the animal with a pumpkin, Harry can direct it to any of the remaining pumpkins. In order to pass the exam, Harry must lead the elephpotamus so that it eats as many pumpkins as possible before it comes across its footprints.

Input
The first input line contains the number of pumpkins on the lawn N (3 ≤ N ≤ 30000). The pumpkins are numbered from 1 to N, the number one being assigned to the pumpkin to which the animal is brought at the start of the trial. In the next N lines, the coordinates of the pumpkins are given in the order corresponding to their numbers. All the coordinates are integers in the range from −1000 to 1000. It is guaranteed that there are no two pumpkins at the same location and there is no straight line passing through all the pumpkins.

Output
In the first line write the maximal number K of pumpkins that can be fed to the elephpotamus. In the next K lines, output the order in which the animal will eat them, giving one number in a line. The first number in this sequence must always be 1.

Sample
input

4
0 0
10 10
0 10
10 0

output

4
1
3
2
4
