def translation(dic, list):
    export_translation=""
    list = (list.strip("[]")).split(",")
    for i in list:
        export_translation += dic[i]

    return export_translation
        


file = open("gesture.config", "r")
export_file = open("new_config.cpp" ,"w")

dic={}
gesture_count=0
gesture_list=[]
gesture_dic={}
hw_count=0
hw_list=[]

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

        elif(line[0]=="Gesture"):
            gesture_count+=1
            if(line[1]=="spc"):
                line[3] = '" "'
                line[4] = line[5]
            gesture_dic[line[1]]=len((line[2].strip("[]")).split(","))
            export += line[0]+" "+line[1]+" = "+line[0]+'("'+translation(dic, line[2])+'", '+str(len((line[2].strip("[]")).split(",")))+", "+line[3]+", "+line[4]+");"
            export_file.write(export)
            export_file.write("\n")

        elif(line[0]=="HandWriting"):
            hw_count+=1
            hw_list.append(line[1])
            if(len(line)==6):
                export += line[0]+" "+line[1]+" = HandWriting("+line[2]+", "+line[3]+", "+line[4]+", "+line[5]+");"
            elif(len(line)==7):
                export += line[0]+" "+line[1]+" = HandWriting("+line[2]+", "+line[3]+", "+line[4]+", "+line[5]+", "+line[6]+");"

            export_file.write(export)
            export_file.write("\n")

    except IndexError:
        export_file.write("\n")

gesture_dic=sorted(gesture_dic.items(), key=lambda x:x[1], reverse=True)
for k,v in gesture_dic:
    gesture_list.append(k)
gesture_list_str=', '.join(gesture_list)
export_gesture_list="Gesture ges_lst["+str(gesture_count)+"]=["+gesture_list_str+"]"
export_file.write(export_gesture_list)
export_file.write("\n")

hw_list_str=', '.join(hw_list)
export_hw_list="HandWriting hw_list["+str(hw_count)+"]=["+hw_list_str+"]"
export_file.write(export_hw_list)
export_file.write("\n")

file.close()
export_file.close()