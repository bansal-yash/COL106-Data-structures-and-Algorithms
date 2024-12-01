from hugchat import hugchat
from hugchat.login import Login
import sys

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 api_call.py API_KEY num_paragraphs query.txt")
        sys.exit(1)

    num_paragraphs = int(sys.argv[1])
    print(num_paragraphs)

    paragraphs = []

    for i in range(num_paragraphs):
        filename = "paragraph_" + str(i) + ".txt"
        with open(filename, "r") as f:
            paragraphs.append(f.read())
            paragraphs.append("\n")

    query_file = sys.argv[2]
    with open(query_file, "r") as f:
        query = f.read()
        paragraphs.append(query)
        paragraphs.append("\n")

    paragraphs = "\n".join(paragraphs)

    print(paragraphs)

    sign = Login("", "")
    cookies = sign.login()

    cookie_path_dir = "./cookies_snapshot"
    sign.saveCookiesToDir(cookie_path_dir)

    chatbot = hugchat.ChatBot(cookies=cookies.get_dict())
    id = chatbot.new_conversation()
    chatbot.change_conversation(id)

    query_result = chatbot.query(paragraphs)
    print(query_result)

    chatbot.delete_all_conversations()