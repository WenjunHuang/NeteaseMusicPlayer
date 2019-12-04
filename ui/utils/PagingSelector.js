function createPageModelItem() {
    // 必须创建一个QtObject，否则function对象无法传递到delegate
    return Qt.createQmlObject(
                "import QtQuick 2.0;QtObject{property var text;property var selected;property var click;}",
                root, "dynamicItem")
}

function createPageModel() {
    let result = []
    // 如果总页数少于columnCount，那么直接生成item即可
    if (totalPageCount <= columnCount) {
        for (let i = 1; i <= totalPageCount; i++) {
            let data = createPageModelItem()
            data.text = i
            data.selected = i === selectedPage
            data.click = function () {
                if (i !== selectedPage)
                    root.offset = (i - 1) * limit
            }

            result.push(data)
        }
        return result
    }

    // 如果选中页是在中间位置
    const ifSelectedAt = Math.floor(columnCount / 2)

    // 计算当前页与首页和最后一页之间的“距离”
    const distanceFromBegin = selectedPage - 1
    const distanceToEnd = totalPageCount - selectedPage

    if (distanceFromBegin > (ifSelectedAt - 1) && distanceToEnd > (columnCount - ifSelectedAt)) {
        // 选中页面距离头尾都足够远
        const head = createPageModelItem()
        head.text = 1
        head.selected = false
        head.click = function(){
            root.offset = 0
        }

        const dot = createPageModelItem()
        dot.text = "..."

        result.push(head,dot)

        for(let i = 3;i <= columnCount - 2;i++) {
            const item = createPageModelItem()
            const page = selectedPage + i - ifSelectedAt
            item.text = page
            item.selected = page === selectedPage
            item.click = function() {
                if (page !== selectedPage)
                    root.offset = (page - 1) * limit
            }
            result.push(item)
        }

        const tail = createPageModelItem()
        tail.text = totalPageCount
        tail.selected = false
        tail.click = function() {
            root.offset = (totalPageCount - 1) * limit
        }
        result.push(dot,tail)

        return result
    }

    if (distanceFromBegin <= (ifSelectedAt - 1)) {
        // 离头部很近
        for (let i = 1;i <= columnCount - 2;i++) {
            const item = createPageModelItem()
            item.text = i
            item.selected = i === selectedPage
            item.click = function() {
                if (i !== selectedPage)
                    root.offset = (i - 1) * limit
            }
            result.push(item)
        }

        const dot = createPageModelItem()
        dot.text = "..."

        const tail = createPageModelItem()
        tail.text = totalPageCount
        tail.click = function() {
            root.offset = (totalPageCount - 1) * limit
        }

        result.push(dot,tail)

        return result
    }

    if (distanceToEnd <= (totalPageCount - ifSelectedAt)) {
        // 离尾部很近
        const head = createPageModelItem()
        head.text = 1
        head.click = function() {
            root.offset = 0
        }
        const dot = createPageModelItem()
        dot.text = "..."

        result.push(head,dot)

        for (let i = 3;i<=columnCount;i++) {
            const item = createPageModelItem()
            const page = totalPageCount - (columnCount - i)
            item.text = page
            item.selected = page === selectedPage
            item.click = function() {
                if (page !== selectedPage)
                    root.offset = (page - 1) * limit
            }

            result.push(item)
        }

        return result
    }


}
