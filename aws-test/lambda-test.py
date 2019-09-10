import requests

headers = {
    'x-api-key': '9qpedDZnN4adQdu0RkMQA534QThmsx3g2iNtV29V',
}

params = (
    ('number', '3'),
)

response = requests.get('https://t75dghia97.execute-api.us-east-2.amazonaws.com/default/sample/', headers=headers, params=params)
