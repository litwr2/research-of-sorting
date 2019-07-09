var M = 3 //max index

function precRound(n) {
    if (precision == 0)
        return n
    return Math.round(n*precision)/precision
}

function changeCheck(s) {
    document.getElementById(s).checked = !document.getElementById(s).checked
    if (document.getElementById(s).checked)
       delete marked[s]
    else
       marked[s] = 1
    drawTable1()
}

function changeOrd(n) {
    sortOrder[n] = trans[sortOrder[n] + 1]
    for (var i = 0; i <= M; ++i)
        if (i != n)
            sortOrder[i] = 0
    drawTable1()
}

function sortCompare(a, b, i) {
    var k = i
    while (typeof(a[i]) == "string" && i > 0) --i
    if (i == 0 && typeof(b[1]) == "string") return 0
    if (i == 0) return -sortOrder[k]
    while (typeof(b[i]) == "string" && i > 0) --i
    if (i == 0) return sortOrder[k]
    return (a[i] - b[i])*sortOrder[k]
}

function drawTable1() {
    var i
    var sortm
    var ta = []
    for (sortm in Data1[order[0]][type[0]]) {
        var el = [ sortm ]
        for (var k = 0; k < M; ++k)
            el.push(Data1[order[0]][type[0]][sortm][k])
        ta.push(el)
    }
    if (sortOrder[0] != 0)
        ta.sort(function(a, b){ if (a[0] > b[0]) return sortOrder[0]; if (a[0] < b[0]) return -sortOrder[0]; return 0 })
    for (i = 1; i <= M; ++i)
        if (sortOrder[i] != 0)
            ta.sort(function(a, b){ return sortCompare(a, b, i) })
    var text = "<tr><th rowspan=2>#<th rowspan=2>Алгоритм<button onclick=changeOrd(0) style='padding:0px 0px;margin:0px 5px'>" + orderArrows[sortOrder[0] + 1] + "</button><th colspan=5>Размер данных"
    text += "<tr>"
    for (i = 0; i < M; ++i)
        text += "<th align=center>10<sup>" + (i + 3).toString()
            + "</sup><button onclick=changeOrd(" + (i + 1).toString()
            + ") style='padding:0px 0px;margin:0px 5px'>" + orderArrows[sortOrder[i + 1] + 1] + "</button>"
    var n = 0
    for (i = 0; i < ta.length; i++) 
        if (document.getElementById("optionSel").value == 0 || ta[i][0] in marked) {
            text += "<tr><td align=center>" + (++n).toString() + "<input id=" + ta[i][0] + " type=checkbox "
            if (ta[i][0] in marked) text += "checked "
            text += "onclick=changeCheck(\"" + ta[i][0] + "\")><td>" + ta[i][0]
            for (var k = 0; k < M; ++k)
                text += "<td align=right>" + ta[i][k + 1]
        }
    document.getElementById("tab1").innerHTML = text
}

function DataAvg() {
    var sum = 0
    var cnt = 0
    for (var sortm in Data1[order[0]][type[0]])
        for (var i = 0; i < M; ++i) {
            if (typeof(Data[order[0]][type[0]][sortm][i]) == "number") {
                sum += Data[order[0]][type[0]][sortm][i]
                cnt++
            }
        }
    return sum/cnt
}

function DataMedian() {
    var vector = []
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < M; ++i)
            vector.push(Data[order[0]][type[0]][sortm][i])
    vector.sort(function(a, b){ if (typeof(a) == "string") return 1; if (typeof(b) == "string") return -1; return a - b })
    return vector[Math.round(vector.length/2)]
}

function DataMin() {
    var min = 1 << 30
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < M; ++i)
            if (Data[order[0]][type[0]][sortm][i] < min)
                min = Data[order[0]][type[0]][sortm][i]
    return min
}

function DataMax() {
    var max = 0
    for (var sortm in Data1[order[0]][type[0]])
        for (i = 0; i < M; ++i)
            if (Data[order[0]][type[0]][sortm][i] > max)
                max = Data[order[0]][type[0]][sortm][i]
    return max
}

function changeOptRel() {
    var pivot = 1  //absolute
    optionRel = document.getElementById("optionRel").value
    if (optionRel == 1)  //average
        pivot = DataAvg();
    else if (optionRel == 2)  //median
        pivot = DataMedian();
    else if (optionRel == 3)  //minimum
        pivot = DataMin();
    else if (optionRel == 4)  //maximum
        pivot = DataMax();
    for (var sortm in Data[order[0]][type[0]])
        for (var i = 0; i < M; ++i)
            if (typeof(Data[order[0]][type[0]][sortm][i]) == "number")
               Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/pivot)
    drawTable1()
}

function changeOptPrec() {
    if (document.getElementById("optionsPrec").value > 0)
        precision = Math.pow(10, document.getElementById("optionsPrec").value);
    else
        precision = 0
    changeOptRel()
}

function types(n, m) {
    if (n == 1) return type[m]
    return order[m]
}

function drawActionTable1() {
    var sv
    var indexValues = [Data1, Data1[order[0]]]
    var text = ""

    for (var i = 0; i < 2; i++) {
        var iv = i.toString()
        text += "<br><button id=sbutt" + iv + " onclick=changeRow(" + iv + ")>" + sbuttc[duoMode[i]] + "</button>:"

        text += "<select id=select" + iv + "0 onchange=changeAction(" + iv + ",0) style=width:14em>"
        for (sv in indexValues[i]) {
            text += "<option value=" + sv
            if (sv == types(i, 0))
                text += " selected"
            text += ">" + sv + "</option>"
        }
        text += "</select>" 

        if (duoMode[i] == 1) {
            text += " / "
            text += "<select id=select" + iv + "1 onchange=changeAction(" + iv + ",1) style=width:14em>";
            for (sv in indexValues[i]) {
                text += "<option value=" + sv
                if (sv == types(i, 1))
                    text += " selected"
                text += ">" + sv + "</option>"
            }
            text += "</select>"
        }
    }
    document.getElementById("tab1a").innerHTML = text
    var cmpType = ["absolute", "average", "median", "minimum", "maximum"]
    if (duoMode[0] + duoMode[1] == 0) { 
        text = "relation: <select id=optionRel onchange=changeOptRel()>"
        for (var i = 0; i < cmpType.length; ++i) {
            text += "<option value=" + i.toString()
            if (i == optionRel)
                text += " selected"
            text += ">" + cmpType[i] + "</option>"
        }
        text += "</select>"
    } else
        text = ""
    document.getElementById("rel").innerHTML = text
}

function changeOptAll() {
    if (duoMode[0] > 0) {
        for (var sortm in Data1[order[0]][type[0]])
            for (var i = 0; i < M; ++i)
                Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/Data[order[1]][type[0]][sortm][i])
    } else if (duoMode[1] > 0) {
        for (var sortm in Data1[order[0]][type[0]])
            for (var i = 0; i < M; ++i) {
                var b
                if (sortm in Data[order[0]][type[1]])
                    b = Data[order[0]][type[1]][sortm][i]
                else
                    b = 0
                if (b != 0)
                    Data1[order[0]][type[0]][sortm][i] = precRound(Data[order[0]][type[0]][sortm][i]/b)
                else
                    Data1[order[0]][type[0]][sortm][i] = "n/a"
            }
    } else
        changeOptRel()
}

function changeRow(n) {
    if (duoMode[n] == 0)
        duoMode[n] = 1
    else
        duoMode[n] = 0
    for (var i = 0; i < 2; ++i)
        if (i != n)
            duoMode[i] = 0
    drawActionTable1()
    changeOptAll()
    drawTable1()
}

function changeAction(n, m) {
    var nms = "select" + n.toString() + m.toString()
    if (n == 1)
        type[m] = document.getElementById(nms).value
    else
        order[m] = document.getElementById(nms).value
    changeOptAll()
    drawTable1()
}

