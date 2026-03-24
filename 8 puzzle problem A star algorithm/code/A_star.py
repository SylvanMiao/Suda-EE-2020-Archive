import heapq
import math
import time








def reverse_count(state):
    inversion_count = 0
    for i in range(8):
        for j in range(i + 1, 9):
            if state[i] != 0 and state[j] != 0 and state[i] > state[j]:
                inversion_count += 1
    return inversion_count

start_time = time.time()
def A_star(start, target):
    def get_f(node):
        return get_g(node) + get_h_manhattan(node)

    def get_g(node):
        return node.depth

    def get_h_manhattan(node):
        h = 0
        for i in range(9):
            if node.state[i] == 0:
                continue
            h += abs(i % 3 - target.index(node.state[i]) % 3) + abs(i // 3 - target.index(node.state[i]) // 3)
        return h

    def get_h_Euclid(node):
        h = 0
        for i in range(9):
            if node.state[i] == 0:
                continue
            x1, y1 = i % 3, i // 3
            x2, y2 = target.index(node.state[i]) % 3, target.index(node.state[i]) // 3
            h += math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)
        return h

    class Node:
        def __init__(self, state, depth, parent, action):
            self.state = state
            self.depth = depth
            self.parent = parent
            self.action = action

        def __lt__(self, other):
            return get_f(self) < get_f(other)

    def expand(node):
        nodes = []
        i = node.state.index(0)
        if i >= 3:
            nodes.append(Node(swap(node.state, i, i - 3), node.depth + 1, node, 'UP'))
        if i < 6:
            nodes.append(Node(swap(node.state, i, i + 3), node.depth + 1, node, 'DOWN'))
        if i % 3 > 0:
            nodes.append(Node(swap(node.state, i, i - 1), node.depth + 1, node, 'LEFT'))
        if i % 3 < 2:
            nodes.append(Node(swap(node.state, i, i + 1), node.depth + 1, node, 'RIGHT'))
        return nodes

    def swap(state, i, j):
        state = state[:]
        state[i], state[j] = state[j], state[i]
        return state


    start_node = Node(start, 0, None, None)
    frontier = [start_node]
    closed = set()
    while frontier:
        node = heapq.heappop(frontier)
        if node.state == target:
            path = []
            while node.parent:
                path.append(node.action)
                node = node.parent
            return path[::-1]
        closed.add(tuple(node.state))
        
        for child in expand(node):
            if tuple(child.state) not in closed:
                heapq.heappush(frontier, child)




# 示例
start = [5, 7, 4,6,3,8,0,1,2]
target = [1, 2, 3, 8, 0, 4, 7, 6, 5]
if reverse_count(start) % 2 == reverse_count(target) % 2:
    print("逆序对数奇偶性符合要求，解如下：")
    path = A_star(start, target)
    print(path)
    end_time = time.time()
    run_time = end_time - start_time
    print("程序运行时间：", run_time, "秒")
else:
    print("逆序对数奇偶性不符合要求，无解")
    end_time = time.time()
    run_time = end_time - start_time
    print("程序运行时间：", run_time, "秒")