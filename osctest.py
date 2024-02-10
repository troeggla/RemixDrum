from random import randint, choice
from time import sleep
from pythonosc import udp_client


def main():
    client = udp_client.SimpleUDPClient("127.0.0.1", 9999)

    for x in range(500):
        route = choice(["/gyx", "/gyy", "/gyz", "/value"])
        value = randint(0, 1) if route == "/value" else randint(0, 180)

        print("Sending", route, value)
        client.send_message(route, value)

        sleep(0.1)


if __name__ == "__main__":
    main()
