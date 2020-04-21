galleryImg = document.querySelectorAll('.gallery-thumbnail')
expandedImg = document.querySelector('#expanded-img')


galleryImg.forEach(image => {
    image.addEventListener("click", function() {
        let newNode = this.cloneNode(true)
        newNode.classList.add("large-img")
        if (newNode.tagName === "VIDEO") {
            newNode.controls = true
        }
        if (expandedImg.hasChildNodes()) {
            expandedImg.replaceChild(newNode, expandedImg.childNodes[0])
        } else {
            expandedImg.appendChild(newNode)
        }
    })
})
