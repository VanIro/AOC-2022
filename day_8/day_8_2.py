inp = open('input.txt','r')
scores = []
columns = None
for line in inp:
    scores_row=[]
    if(line[-1]=='\n'): line=line[:-1]
    for i in range(len(line)):
        score=0
        for j,c in enumerate(reversed(line[0:i])):
            score+=1
            if c >= line[i]: break
        if score>0:
            rscore = 0
            for j,c in enumerate(line[i+1:]):
                rscore+=1
                if c >= line[i]: break
            score*=rscore
        scores_row.append(score)
    # print(scores_row)
    scores.append(scores_row)
    if columns==None:
        columns = [c for c in line]
    else:
        for i,c in enumerate(line):
            columns[i]+=c
        
for k,line in enumerate(columns):
    scores_row=[]
    for i in range(len(line)):
        if line[i]=='\n':
            continue
        score=0
        for j,c in enumerate(reversed(line[0:i])):
            score+=1
            if c >= line[i]: break
        if score>0:
            rscore = 0
            for j,c in enumerate(line[i+1:]):
                rscore+=1
                if c >= line[i]: break
            score*=rscore
        scores[i][k]*=score

import itertools
scores = list(itertools.chain.from_iterable(scores))
# print(scores[1:-1])
print(max(scores))


