with open('./0102_input.txt', 'r') as input:
    content = input.read()

def getPoints(row):
    xy = row.split(',')
    return [(int(xy[0]), int(xy[1])),   \
            (int(xy[2]), int(xy[3])),   \
            (int(xy[4]), int(xy[5]))]

def inRange(v, r1, r2):
    return v >= min(r1, r2) and v <= max(r1, r2)

def xmul(pp, p1, p2):
    # 向量(pp-p1)和(p2-p1)的叉积
    if p1[1] > p2[1]:
        p1,p2 = p2,p1

    return (pp[0]-p1[0]) * (p2[1]-p1[1]) - (pp[1]-p1[1]) * (p2[0]-p1[0])

def intersect(pp, p1, p2):
    # 判断以pp为起始点向左的射线是否和线段p1p2相交
    # 约定如果和顶点相交只认可Y坐标比较大的顶点，避免重复计算
    return inRange(pp[1], p1[1], p2[1]) and \
        pp[1] != min(p1[1], p2[1]) and  \
        xmul(pp, p1, p2) < 0

def inEdge(pp, p1, p2):
    # 判断点pp是否在线段p1p2上
    return inRange(pp[0], p1[0], p2[0]) and \
            inRange(pp[1], p1[1], p2[1]) and \
            xmul(pp, p1, p2) == 0

def inPolygon(p, points):
    for i in range(0,3):
        if inEdge(p, points[i], points[(i+1)%len(points)]):
            return True

    counter = 0
    for i in range(0,3):
        if intersect(p, points[i], points[(i+1)%len(points)]):
            counter += 1
    
    return counter % 2 == 1
    
ls = content.split('\n')
ls = [getPoints(row) for row in ls if row]

# test case
# ls = [
#     [(-1,-1),(9,1),(1,9)],
#     [(0,0),(9,1),(1,9)],
#     [(1,1),(9,1),(1,9)],
# ]


result = 0
for points in ls:
    if inPolygon((0,0), points):
        result += 1

print(result)

# 计算几何
# 凸多边形包含点判定
# 方案1：通过(0,0)发出的射线和多边形相交次数判定点是否在多边形内

# 方案2：用海伦公式计算三角形面积和，比较顶点两两和顶点组成的小三角形面积之和

# 论坛里有人总结了相当多方法
# https://projecteuler.net/best_posts=102