import UIKit

// 队列可以保证元素存入和取出的顺序是先进先出(first-in first-out, FIFO)

struct Queue<T> {
    var queue: [T?] = []
    var head: Int = 0 // 通过index 可以提高出栈时候的效率
    
    public var isEmpty: Bool {
        return count == 0
    }
    
    public var count: Int {
        return queue.count - head
    }
    
    public var front: T? {
        if isEmpty {
            return nil
        }
        return queue[head]
    }
    
    public mutating func enqueue(_ element: T) {
        queue.append(element)
    }
    
    public mutating func dequeue() -> T? {
        guard head < queue.count, let element = queue[head] else { return nil }
        queue[head] = nil
        head += 1
        let percentage = Double(head) / Double(queue.count)
        if queue.count > 50 && percentage > 0.25 {
            queue.removeFirst(head)
            head = 0
        }
        return element
    }
}

var queue = Queue.init(queue: ["1A"], head: 0)
queue.enqueue("2B")
queue.enqueue("3C")
queue.dequeue()
print(queue.queue)
