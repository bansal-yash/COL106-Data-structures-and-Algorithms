-------------------------------------------------------------------------------------------------------
Before running the code:
Make sure that python3, hugchat and openai are installed.
To install openai:
>> pip install openai==0.28
To install hugchat:
>> pip install hugchat

To run the file, keep all the 98 books of the corpus in the same folder as all the source 
codes and header files. 

To compile the executable and run the code, on the command line, write 
>> g++ tester.cpp qna_tool.cpp Node.cpp dict.cpp (on LINUX or WSL terminal)
>> ./a.out
or
>> g++ tester.cpp qna_tool.cpp Node.cpp dict.cpp (on WINDOWS CMD)
>> a.exe

You will be asked to enter your query. The query must be on one line only without line breaks.
You will then be asked to choose the algorithm for selecting top k paragraphs: 
enter 1 to select the algorithm used to find top k paragraphs 
as in part 1 of the assignment or enter 2 to select BM25 algorithm. You will then be asked the 
value of k. Note that if you want to use chatGPT to find the output of your query you can only 
give a maximum of about 4000 tokens (words) so the value of k should not be given too large in 
this step. You are then asked to select the LLM to process the query : 1 for chatGPT, 2 for 
HuggingChat. If you choose BM25 algorithm to process top k paragraphs, you will also be asked the
value of parameter b in the BM25 scoring formula. b must be between 0.5 and 1, both inclusive. 
The top k paragraphs are printed to STDOUT in separate lines in the format:
Book_code: (book code) Page: (page num) Paragraph: (paragraph num)
Then all the k paragraphs are printed in decreasing order of scores.
Then the query given to LLM is printed and then the output is printed.

Make sure to delete all the extra files paragraph_[i].txt made for top i-th paragraph and query.txt
before running the code another time.
--------------------------------------------------------------------------------------------------------