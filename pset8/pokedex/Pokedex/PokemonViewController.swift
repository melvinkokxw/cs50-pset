import UIKit

class PokemonViewController: UIViewController {
    var url: URL!
    var caught: Bool = false

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var spriteImageView: UIImageView!
    @IBOutlet var flavorTextView: UITextView!
    
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
        loadFlavourText()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: url!) { (data, response, error) in
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
                            self.type1Label.text = self.capitalize(text: typeEntry.type.name)
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = self.capitalize(text: typeEntry.type.name)
                        }
                    }
                    
                    if let spriteData = try? Data(contentsOf: result.sprites.front_default) {
                        if let image = UIImage(data: spriteData) {
                            self.spriteImageView.image = image
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
    
    func loadFlavourText() {
        let id = url.lastPathComponent
        let speciesURL = URL(string: "https://pokeapi.co/api/v2/pokemon-species/" + id)
        URLSession.shared.dataTask(with: speciesURL!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonSpeciesResult.self, from: data)
                DispatchQueue.main.async {
                    let flavor_text_entries = result.flavor_text_entries
                    for entry in flavor_text_entries {
                        if entry.language.name == "en" {
                            self.flavorTextView.text = entry.flavor_text.replacingOccurrences(of: "\\s", with: " ", options: .regularExpression)
                            self.flavorTextView.isEditable = false
                            break
                        }
                    }
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
}
