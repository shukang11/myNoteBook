import UIKit

// 队列可以保证元素存入和取出的顺序是先进先出(first-in first-out, FIFO)

struct Queue<T> {
    var queue: [T] = []
    
    public var isEmpty: Bool {
        return queue.isEmpty
    }
    
    public var count: Int {
        return queue.count
    }
    
    public var front: T? {
        return queue.first
    }
    
    public mutating func enqueue(_ element: T) {
        queue.append(element)
    }
    
    public mutating func dequeue() -> T? {
        if isEmpty {
            return nil
        }
        return queue.removeFirst()
    }
}

var queue = Queue.init(queue: ["1A"])
queue.enqueue("2B")
queue.enqueue("3C")
queue.dequeue()
print(queue.queue)
