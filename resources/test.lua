function start()
    print("Starting")

    firstTime = true
end

function update(delta)
    if firstTime then
        firstTime = false
        print("Updating with delta: "..delta)
    end
end
