import openai
import sys

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python3 api_call.py API_KEY num_paragraphs query.txt")
        sys.exit(1)

    openai.api_key = sys.argv[1]
    num_paragraphs = int(sys.argv[2])
    print(num_paragraphs)

    paragraphs = []

    for i in range(num_paragraphs):
        filename = "paragraph_" + str(i) + ".txt"
        with open(filename, "r") as f:
            paragraphs.append(f.read())
            paragraphs.append("\n")

    query_file = sys.argv[3]
    with open(query_file, "r") as f:
        query = f.read()
        paragraphs.append(query)
        paragraphs.append("\n")

    paragraphs = "\n".join(paragraphs)

    print(paragraphs)

    query = {"role": "user", "content": paragraphs}

    chat = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=[query])

    reply = chat.choices[0].message.content
    print(reply)