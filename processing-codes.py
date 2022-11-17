#!python3
# processing the json files for CSS codes

import os            #mv files
import fileinput     #read (json) files
import json
import datetime

def pretty_2D_list(table):
    n=0
    string = ''
    for row in table[n:]:
        print('    n='+str(n)+':\t'+str(row))
        string += 'n='+str(n)+':\t'+str(row) +'\n'
        n+=1
    return string
#        print(row)
#        print(''.join(str(row)))

# not in use. too slow compared to system bash commands
def get_json_list():
    path_of_the_directory = '../data/CSS-Codes/run1'
    ext = ('.json')
    for files in os.scandir(path_of_the_directory):
        if files.path.endswith(ext):
            print(files) 
            print(files.name)
            print(files.path[:-5])
            break

#get_json_list()
#exit()

def main():
    print(r'''    This function exract max [n,k,d] and save d in a 2D array/list with respect to n and k.
    Invalid json will be skipped and reported. They exist due to parallel file writing when generating codes on qlab''')
    data_folder = "json1"
#    data_folder = "codes" 
    data_folder = '../data/CSS-Codes/run1'
    trash_folder = '../data/CSS-Codes/trash'
#    filename_list = '../data/CSS-Codes/filelist-run1.txt'
    filename_list = 'filelist-run1.txt'  #./get-filelist.sh
    log_file = 'run.log'

    print('data_folder:\t'+data_folder)
    print('trash_folder:\t'+trash_folder)
    print('filename_list:\t'+filename_list)
    print('log_file:\t'+log_file)
    print(datetime.datetime.now())

    num_of_codes=0   
    n,k,d=-1,-1,-1
    max_distance_table=[[ 0 for k in range(25)] for n in range(31) ]
    max_distance_table[0]=[_ % 10 for _ in range(25)]
    # d=table[n][k]

    for line in fileinput.input(filename_list):
        num_of_codes += 1
        if (num_of_codes % 10000 == 0):
            print('finish processing '+str(num_of_codes)+' codes')
        try:
            with open(data_folder+'/'+ line[:-1]+'','r') as fjson:
                js = json.load(fjson)
                n,k,d=js['n'],js['k'],js['d']
                if d > max_distance_table[n][k]:
                    max_distance_table[n][k] = d
        except:
            print('invalid json: '+line)
            # move it to trash
            os.system('mv '+ data_folder+'/'+ line[:-1]+' ' +data_folder+'/'+ line[:-6]+'Gx.mm '+data_folder+'/'+ line[:-6]+'Gz.mm ' +trash_folder)
            print(line+' moved to trash')

    print('[n,k,d] table')
    string = pretty_2D_list(max_distance_table)
    print(["total number of codes:", num_of_codes])
    print(datetime.datetime.now())

    with open(log_file,'a') as f:
        f.write(string)


def test():
        with open('codes/n15k3d2-x5z7dx3dz2-1.json','r') as fjson:
            print(fjson.read())
            js = json.load(fjson)
            print(js)
            n,k,d=js['n'],js['k'],js['d']
            if d > max_distance_table[n][k]:
                max_distance_table[n][k] = d

#test()
#exit()

main()

    
