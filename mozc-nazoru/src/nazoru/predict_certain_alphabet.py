def predict_certain_alphabet(data):
    event_list = [d[0] for d in data]
    if event_list == ["y", "h", "n"] or event_list == ["y" , "n"]:
        result = "l"
    elif event_list[-1] == "y":
        if sorted(set(event_list), key=event_list.index) == ["h", "n", "y"] or sorted(set(event_list), key=event_list.index) == ["h" , "y"]:
            result = "i"
        else:
            result = "j"
    elif event_list[0] == "t" and event_list[len(event_list)-1] == "m":
        result = "n"
    elif event_list[0] == "g" and "g" in event_list[1:]:
        result = "e"
    elif event_list[0] == "g" and event_list[len(event_list)-1] == "m":
        result = "t"
    elif event_list[0] == "u" and event_list[len(event_list)-1] == "m":
        if len(event_list) > 8:
            result = "c"
        else:
            result = "a"


    return result