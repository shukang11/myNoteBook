import UIKit
import Foundation

public struct Stack<T> {
    fileprivate var array = [T]()
    
    public var isEmpty: Bool {
        return array.isEmpty
    }
    
    public var count: Int {
        return array.count
    }
    
    public mutating func push(_ element: T) {
        array.append(element)
    }
    
    public mutating func pop() -> T? {
        return array.popLast()
    }
    
    public var top: T? {
        return array.last
    }
}

// 遍历
extension Stack: Sequence {
    public func makeIterator() -> AnyIterator<T> {
        var curr = self
        return AnyIterator.init({ () -> T? in
            return curr.pop()
        })
    }
}

var stackOfName = Stack.init(array: ["小明", "小强", "小戎", "张三", "李四"])
// 想栈顶部添加一个元素
stackOfName.push("王麻子")
stackOfName.push("李狗子")

for name in stackOfName {
    print("\(name)")
}
