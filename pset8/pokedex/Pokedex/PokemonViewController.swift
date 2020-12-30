import UIKit

class PokemonViewController: UIViewController {
    var url: String!
    var caught: Bool = false

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var spriteImage: UIImageView!
    
    @IBAction func toggleCatch() {
        caught = !caught
        UserDefaults.standard.set(caught, forKey: nameLabel.text!)
        catchButton.setTitle(caught ? "Release" : "Catch", for: UIControl.State.normal)
    }

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""

        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)

                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                    
                    if let spriteData = try? Data(contentsOf: result.sprites.front_default) {
                        if let image = UIImage(data: spriteData) {
                            DispatchQueue.main.async {
                                self.spriteImage.image = image
                            }
                        }
                    }
                    
                    
                    self.caught = UserDefaults.standard.bool(forKey: self.nameLabel.text!)
                    self.catchButton.setTitle(self.caught ? "Release" : "Catch", for: UIControl.State.normal)
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
}
