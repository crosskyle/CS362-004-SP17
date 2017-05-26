/*
 
 Author: Kyle Cross

When first looking at the testme() method, I didn't understand how the chain of if statements was working. Then I realized that since state was initialized outside of the while loop scope, the state would be saved after each if statement condition was found to be true. So I came to the conclusion that just returning any random character value from inputChar() would eventually lead to a state of 9.
 
 The function inputChar() returns a random value that could be any ASCII character. Even though there are 127 characters that could possibly be returned, it does not take long for the random tester to reach state 9.
 
 The function inputChar() finds the correct values by constantly spitting out random characters, each of which have the possiblility to pass the if conditionals.
 
 Returning the correct random value for inputString() proved to be more challenging. I ended up narrowing down the scope of the tester to be much smaller than what I originally started with. Originally, I allowed each character of the 5 character length string to be any ASCII character. This proved to be too large of a scope. It could take forever to find the five characters in the correct order from a possibility of 127 characters. Therefore, I ended up limiting the random tester scope to just 4 characters 'r', 'e', 's', and 't'. This proved to be a more successful random tester because it was able to find the correct ordering of the 5 characters rather quickly. Even though the scope is much narrower, it still tests for all the possible orderings of some character set.
 
 The function inputString() finds the correct value by constantly spitting out some permutation of the characters 'r', 'e', 's', and 't' which make a length of 5 characters total. The sixth element in the returned value is always null to limit the possible return value to 5 characters.
 
 Depending on how much time is available to the tester, the scope of both random testers could be altered as necessary. However, this random tester's scope is good enough to catch the error in testme().

*/
