def translation(dic, list):
    export_translation=""
    list = (list.strip("[]")).split(",")
    for i in list:
        export_translation += dic[i]

    return export_translation
        


file = open("gesture.config", "r")
export_file = open("new_config.cpp" ,"w")

dic={}
count=0
gesture_list=[]

for line in file:
    export = ""
    line=line.replace(", ",",")
    line = line.split()
    try:
        if (line[0]=="Key"):
            dic[line[1]]=line[3]
            true_or_false="false"
            if(line[3]=="d" or line[3]=="s" or line[3]=="c"):
                true_or_false="true"
            export += line[0]+" "+line[1]+" = "+line[0]+"("+line[2]+', "'+line[1]+'", "'+line[3]+'", wearbo, '+true_or_false+");"
            export_file.write(export)
            export_file.write("\n")

        if(line[0]=="Gesture"):
            count=count+1
            gesture_list.append(line[1])
            if(line[1]=="spc"):
                line[3] = '" "'
                line[4] = line[5]
            export += line[0]+" "+line[1]+" = "+line[0]+'("'+translation(dic, line[2])+'", '+str(len((line[2].strip("[]")).split(",")))+", "+line[3]+", "+line[4]+");"
            export_file.write(export)
            export_file.write("\n")
    except IndexError:
        export_file.write("\n")

gesture_list.sort(reverse=True, key=len)
gesture_list_str=', '.join(gesture_list)
export_list="gesture["+str(count)+"]=["+gesture_list_str+"]"
export_file.write(export_list)
export_file.write("\n")

file.close()
export_file.close()